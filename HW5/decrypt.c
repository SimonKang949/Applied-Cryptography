//
//  decrypt.c
//  HW5
//
//  Created by Simon Kang on 4/1/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int tablecheck(FILE * tablefile);
int check_hex(char check);
void key_expansion(unsigned char init_key[16], unsigned char round_key[44][4], FILE* tablefile);
int format_s(unsigned char * s_box, FILE * tablefile);
int add_round_key(unsigned char state[4][4], unsigned char round_key[44][4], int round);
int sub_bytes(unsigned char state[4][4], unsigned char * s_box);
int mix_columns(unsigned char state[4][4], unsigned char * poly);


void inv_shift_rows(unsigned char state[4][4])
{
    unsigned char temp[3];
    int row = 0;
    int col = 0;
    int i = 0;
    
    for(row=1; row<4; row++)
    {
        for(i=3; i>=4-row; i--)
        {
            temp[i+row-4] = state[row][i];
        }
        
        for(col=3; col>=0; col--)
        {
            if((col-row) >= 0)
            {
                state[row][col] = state[row][col-row];
            }
            else
            {
                state[row][col] = temp[col];
            }
        }
    }
}



int format_inv_poly(unsigned char* poly, FILE* table)
{
    const char* header = "INVP=";
    char* poly_buffer = (char*)calloc(1,32);
    char temp_values[3];
    unsigned int i = 0;
    
    fseek(table, 0, SEEK_SET);
    while(strncmp(poly_buffer, header, strlen(header)) != 0)
    {
        if(!fgets(poly_buffer, 32, table))
        {
            fprintf(stderr, "No P line was found\n");
            exit(1);
        }
    }
    poly_buffer += strlen(header);
    
    
    for(i=0; i<4; i++) {
        temp_values[0] = poly_buffer[i*2];
        temp_values[1] = poly_buffer[i*2+1];
        temp_values[2] = ' ';
        poly[i] = strtol(temp_values, NULL, 16);
    }
    
    return 0;
}


int format_invert_s(unsigned char * s_box, unsigned char * inv_s_box)
{
    int i = 0;
    
    for(i=0; i<256; i++)
    {
        inv_s_box[ s_box[i] ] = i;
    }
    return 0;
}


int inv_print_state(unsigned char state[4][4], int round, const char* header, int flag)
{
    int i = 0;
    
    if(!flag)
    {
        return 0;
    }
    
    if(round < 10)
    {
        fprintf(stdout, "round[ %d].%s   ", round, header);
    }
    else
    {
        if(strcmp(header, "ioutput") == 0)
        {
            fprintf(stdout, "round[%d].%s  ", round, header);
        }
        else
        {
            fprintf(stdout, "round[%d].%s   ", round, header);
        }
    }
    
    if(strcmp(header, "ik_sch") == 0)
    {
        for(i=0; i<16; i++)
        {
            fprintf(stdout, "%02x", state[i/4][i%4]);
        }
    }
    else
    {
        for(i=0; i<16; i++)
        {
            fprintf(stdout, "%02x", state[i%4][i/4]);
        }
    }
    fprintf(stdout, "\n");
    return 0;
}

int decrypt_block(unsigned char cipher_buffer[16], unsigned char output_buffer[16], unsigned char round_key[44][4], FILE* tablefile, int flag)
{
    unsigned char state[4][4] = { { 0 } };
    unsigned char * inv_poly = (unsigned char*)calloc(1,4);
    unsigned char * s_box = (unsigned char*)calloc(1,256);
    unsigned char * inv_s_box = (unsigned char*)calloc(1,256);
    int i = 0;
    
    format_s(s_box, tablefile);
    format_invert_s(s_box, inv_s_box);
    format_inv_poly(inv_poly, tablefile);
    
    for(i=0; i<16; i++)
    {
        state[i%4][i/4] = cipher_buffer[i];
    }
    
    inv_print_state(state, 0, "iinput", flag);
    inv_print_state(&(round_key[4*10]), 0, "ik_sch", flag);
    
    add_round_key(state, round_key, 10);
    
    for(i=9; i>0; i--)
    {
        inv_print_state(state, 10-i, "istart", flag);
        
        inv_shift_rows(state);
        inv_print_state(state, 10-i, "is_row", flag);
        
        sub_bytes(state, inv_s_box);
        inv_print_state(state, 10-i, "is_box", flag);
        
        inv_print_state(&(round_key[4*i]), 10-i, "ik_sch", flag);
        add_round_key(state, round_key, i);
        inv_print_state(state, 10-i, "ik_add", flag);
        
        mix_columns(state, inv_poly);
    }
    
    inv_print_state(state, 10, "istart", flag);
    
    inv_shift_rows(state);
    inv_print_state(state, 10, "is_row", flag);
    
    sub_bytes(state, inv_s_box);
    inv_print_state(state, 10, "is_box", flag);
    
    add_round_key(state, round_key, 0);
    inv_print_state(&(round_key[4*0]), 10, "ik_sch", flag);
    
    
    for(i=0; i<16; i++)
    {
        output_buffer[i] = state[i%4][i/4];
    }
    inv_print_state(state, 10, "ioutput", flag);
    
    
    
    return 0;
}



int aes_decrypt(const char * key, FILE * tablefile, FILE * input_file)
{
    unsigned char round_key[44][4] = { { 0 } };
    unsigned char * init_key = (unsigned char*)calloc(1,16);
    unsigned char * cipher_buffer = (unsigned char*)calloc(1,16);
    unsigned char * output_buffer = (unsigned char*)calloc(1,16);
    int i = 0;
    char temp_values[3];
    int flag = 1;
    int size = 0;
    
    tablecheck(tablefile);
    
    if (strlen(key) != 32)
    {
        fprintf(stderr, "bad key\n");
        exit(1);
    }
    
    for(i=0; i<16; i++) {
        if(check_hex(key[i*2]) || check_hex(key[i*2+1]))
        {
            fprintf(stderr, "key values are not hex\n");
            exit(1);
        }
        temp_values[0] = key[i*2];
        temp_values[1] = key[i*2+1];
        temp_values[2] = ' ';
        init_key[i] = strtol(temp_values, NULL, 16);
    }
    
    key_expansion(init_key, round_key, tablefile);
    
    
    while((size = (int)fread(cipher_buffer, 1, 16, input_file)))
    {
        if((*cipher_buffer == '\n') && (size == 1))
        {
            continue;
        }
        
        decrypt_block(cipher_buffer, output_buffer, round_key, tablefile, flag);
        
        flag = 0;
        for(i=0; i<16; i++)
        {
            output_buffer[i] = 0x00;
            cipher_buffer[i] = 0x00;
        }
    }
    
    //printf("this is function aes_decrypt\n");
    return 0;
}
