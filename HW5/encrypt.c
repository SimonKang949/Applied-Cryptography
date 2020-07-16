//
//  encrypt.c
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
int format_s(unsigned char * s_box, FILE * tablefile);
void key_expansion(unsigned char init_key[16], unsigned char round_key[44][4], FILE* tablefile);
unsigned char multiply(unsigned char p1, unsigned char p2);


int mix_columns(unsigned char state[4][4], unsigned char * poly)
{
    unsigned char * col = (unsigned char*)calloc(1,4);
    int i = 0;
    int j = 0;
    int k = 0;
    
    for(i=0; i<4; i++)
    {
        memset(col, 0, 4);
        
        for(j=0; j<4; j++)
        {
            for(k=0; k<4; k++)
            {
                col[j] ^= multiply(state[k][i], poly[ (k-j+3)%4 ]);
            }
        }
        
        for(j=0; j<4; j++)
        {
            state[j][i] = col[j];
        }
    }
    
    return 0;
}


int shift_rows(unsigned char state[4][4])
{
    unsigned char temp[3];
    int row = 0;
    int col = 0;
    int i = 0;
    
    for(row=1; row<4; row++)
    {
        for(i=0; i<row; i++)
        {
            temp[i] = state[row][i];
        }
        
        for(col=0; col<4; col++)
        {
            if((col+row) < 4)
            {
                state[row][col] = state[row][col+row];
            }
            else
            {
                state[row][col] = temp[row+col-4];
            }
        }
    }
    
    return 0;
}


int sub_bytes(unsigned char state[4][4], unsigned char * s_box)
{
    int i = 0;
    int j = 0;
    
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            state[i][j] = s_box[ state[i][j] ];
        }
    }
    
    return 0;
}


int add_round_key(unsigned char state[4][4], unsigned char round_key[44][4], int round)
{
    int i = 0;
    int j = 0;
    
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            state[i][j] ^= round_key[round*4 + j][i];
        }
    }
    
    return 0;
}


int print_state(unsigned char state[4][4], int round, const char* header, int flag)
{
    int i = 0;
    
    if(!flag)
    {
        return 0;
    }
    
    if(round < 10)
    {
        fprintf(stdout, "round[ %d].%s    ", round, header);
    }
    else
    {
        if(strcmp(header, "output") == 0)
        {
            fprintf(stdout, "round[%d].%s   ", round, header);
        }
        else
        {
            fprintf(stdout, "round[%d].%s    ", round, header);
        }
    }
    
    if(strcmp(header, "k_sch") == 0)
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


int format_poly(unsigned char* poly, FILE* table)
{
    const char* header = "P=";
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

int encrypt_block(unsigned char in_buffer[16], unsigned char cipher_buffer[16], unsigned char round_key[44][4], FILE * tablefile, int flag)
{
    unsigned char state[4][4] = { { 0 } };
    unsigned char * poly = (unsigned char*)calloc(1,4);
    unsigned char * s_box = (unsigned char*)calloc(1,256);
    int i = 0;
    
    format_s(s_box, tablefile);
    format_poly(poly, tablefile);
    
    for(i=0; i<16; i++)
    {
        state[i%4][i/4] = in_buffer[i];
    }
    
    
    print_state(state, 0, "input", flag);
    print_state(round_key, 0, "k_sch", flag);
    
    add_round_key(state, round_key, 0);
    
    
    for(i=1; i<10; i++)
    {
        print_state(state, i, "start", flag);
        
        sub_bytes(state, s_box);
        print_state(state, i, "s_box", flag);
        
        shift_rows(state);
        print_state(state, i, "s_row", flag);
        
        mix_columns(state, poly);
        print_state(state, i, "m_col", flag);
        
        add_round_key(state, round_key, i);
        print_state(&(round_key[4*i]), i, "k_sch", flag);
        
    }
    
    
    print_state(state, 10, "start", flag);
    
    sub_bytes(state, s_box);
    print_state(state, 10, "s_box", flag);
    
    shift_rows(state);
    print_state(state, 10, "s_row", flag);
    
    add_round_key(state, round_key, 10);
    print_state(&(round_key[4*10]), 10, "k_sch", flag);
    
    for(i=0; i<16; i++)
    {
        cipher_buffer[i] = state[i%4][i/4];
    }
    print_state(state, 10, "output", flag);
    
    
    return 0;
}


int aes_encrypt(const char * key, FILE * tablefile, FILE * input_file)
{
    unsigned char round_key[44][4] = { { 0 } };
    unsigned char * init_key = (unsigned char*)calloc(1,16);
    unsigned char * in_buffer = (unsigned char*)calloc(1,16);
    unsigned char * cipher_buffer = (unsigned char*)calloc(1,16);
    char temp_values[3];
    int i = 0;
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
    
    
    
    
    while((size = (int)fread(in_buffer, 1, 16, input_file)))
    {
        if((*in_buffer == '\n') && (size == 1))
        {
            continue;
        }
        
        encrypt_block(in_buffer, cipher_buffer, round_key, tablefile, flag);
        
        flag = 0;
        for(i=0; i<16; i++) {
            in_buffer[i] = 0x00;
            cipher_buffer[i] = 0x00;
        }
    }
    
    
    
    //printf("this is function aes_encrypt\n");
    return 0;
}
