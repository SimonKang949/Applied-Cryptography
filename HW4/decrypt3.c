//
//  encrypt3.c
//  HW4
//
//  Created by Simon Kang on 3/12/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_line_format(FILE *fp, int * check_values, char * line_header, int len);
int encrypt_block(unsigned char * block_in, unsigned char * block_out, unsigned char keys[16][6], FILE *fp, int flag);
int decrypt_block(unsigned char * block_in, unsigned char * block_out, unsigned char keys[16][6], FILE *fp, int flag);
int key_generation(FILE *fp, const char * key, unsigned char keys[16][6]);



int decrypt3(FILE *fp, FILE *fp_input, const char * key)
{
    char* key1 = (char*)calloc(1,16);
    char* key2 = (char*)calloc(1,16);
    char* key3 = (char*)calloc(1,16);
    unsigned char keys1[16][6] = { { 0 } };
    unsigned char keys2[16][6] = { { 0 } };
    unsigned char keys3[16][6] = { { 0 } };
    unsigned char* block_in = (unsigned char*)calloc(1,8);
    unsigned char* block_out = (unsigned char*)calloc(1,8);
    
    int size = 0;
    int flag = 0;
    int i = 0;
    
    memcpy(key1, key, 16);
    memcpy(key2, key+16, 16);
    memcpy(key3, key+32, 16);
    
    key_generation(fp, key1, keys1);
    key_generation(fp, key2, keys2);
    key_generation(fp, key3, keys3);
    
    
    while((size = (int)fread(block_in, 1, 8, fp_input)))
    {
        if((*block_in == '\n') && (size == 1))
        {
            continue;
        }
        decrypt_block(block_in, block_out, keys1, fp, flag);
        for(i=0; i<8; i++) block_in[i] = 0x00;
        encrypt_block(block_in, block_out, keys2, fp, flag);
        for(i=0; i<8; i++) block_out[i] = 0x00;
        decrypt_block(block_in, block_out, keys3, fp, flag);
        
        printf("%c%c%c%c%c%c%c%c", *block_out, *(block_out+1), *(block_out+2), *(block_out+3), *(block_out+4), *(block_out+5), *(block_out+6), *(block_out+7) );
        
        flag = 1;
        for(i=0; i<8; i++)
        {
            block_in[i] = 0x00;
            block_out[i] = 0x00;
        }
    }
    
    
    return 0;
}
