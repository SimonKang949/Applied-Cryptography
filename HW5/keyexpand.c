//
//  keyexpand.c
//  HW5
//
//  Created by Simon Kang on 4/1/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Nk 4
#define Nr 10
#define Nb 4

int check_hex(char check);
unsigned char multiply(unsigned char p1, unsigned char p2);


int format_s(unsigned char * s_box, FILE * tablefile)
{
    const char * header = "S=";
    char * s_buffer = (char *)calloc(1, 640);
    char temp_values[3];
    unsigned int i=0;
    
    fseek(tablefile, 0, SEEK_SET);
    while (strncmp(s_buffer, header, strlen(header)) != 0)
    {
        if (!fgets(s_buffer, 640, tablefile ))
        {
            fprintf(stderr, "S line does not be found\n");
            exit(1);
        }
    }
    
    s_buffer += strlen(header);
    
    for(i=0; i<256; i++) {
        temp_values[0] = s_buffer[i*2];
        temp_values[1] = s_buffer[i*2+1];
        temp_values[2] = ' ';
        s_box[i] = strtol(temp_values, NULL, 16);
    }
    
    return 0;
}

void rotating(unsigned char round_key[4])
{
    unsigned char temp_char = round_key[0];
    round_key[0] = round_key[1];
    round_key[1] = round_key[2];
    round_key[2] = round_key[3];
    round_key[3] = temp_char;
}

void key_expansion(unsigned char init_key[16], unsigned char round_key[44][4], FILE* tablefile)
{
    unsigned char * temp = (unsigned char*)calloc(1,4);
    unsigned char * s_box = (unsigned char*)calloc(1,256);
    unsigned char * rc = (unsigned char*)calloc(1,256);
    int i = 0;
    
    format_s(s_box, tablefile);
    
    rc[0] = 0x8d;
    for(i=1; i<256; i++) {
        rc[i] = multiply(rc[i-1], 0x02);
    }
    
    for(i=0; i<4; i++)
    {
        round_key[i][0] = init_key[4*i];
        round_key[i][1] = init_key[4*i+1];
        round_key[i][2] = init_key[4*i+2];
        round_key[i][3] = init_key[4*i+3];
    }
    
    for(i=4; i<44; i++)
    {
        temp[0] = round_key[i-1][0];
        temp[1] = round_key[i-1][1];
        temp[2] = round_key[i-1][2];
        temp[3] = round_key[i-1][3];
        
        if (i%4 == 0)
        {
            rotating(temp);
            temp[0] = s_box[ temp[0] ] ^ rc[i/4];
            temp[1] = s_box[ temp[1] ];
            temp[2] = s_box[ temp[2] ];
            temp[3] = s_box[ temp[3] ];
        }
        
        round_key[i][0] = round_key[i-4][0] ^ temp[0];
        round_key[i][1] = round_key[i-4][1] ^ temp[1];
        round_key[i][2] = round_key[i-4][2] ^ temp[2];
        round_key[i][3] = round_key[i-4][3] ^ temp[3];
    }
    
}





int keyexpand(const char * key, FILE* tablefile)
{
    unsigned char * init_key = (unsigned char*)calloc(1,16);
    unsigned char round_key[Nb*(Nr+1)][4];
    char temp_values[3];
    int i=0;
    
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
    
    for(i=0; i<44; i++)
    {
        if(i >= 10)
        {
            printf("w[%d]: %02x%02x%02x%02x\n", i, round_key[i][0], round_key[i][1], round_key[i][2], round_key[i][3]);
        }
        else
        {
            printf("w[ %d]: %02x%02x%02x%02x\n", i, round_key[i][0], round_key[i][1], round_key[i][2], round_key[i][3]);
        }
    }
    
    
    //printf("%s\n", key);
    //printf("this is function keyexpand\n");
    return 0;
}
