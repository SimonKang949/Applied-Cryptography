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

int key_generation(FILE *fp, const char * key, unsigned char keys[16][6])
{
    int pc1_values[56];
    int pc2_values[48];
    int v_values[16];
    char temp[3];
    temp[2] = ' ';
    unsigned char * hex_key = (unsigned char *)calloc(1, 8);
    unsigned char * C = (unsigned char *)calloc(1, 4);
    unsigned char * D = (unsigned char *)calloc(1, 4);
    unsigned char* T = (unsigned char*)malloc(7);
    
    int i=0;
    int j=0;
    int k=0;
    
    
    if (check_line_format(fp, pc1_values, (char *)"PC1=", 56) || check_line_format(fp, pc2_values, (char *)"PC2=", 48) || check_line_format(fp, v_values, (char *)"V=", 16) )
    {
        fprintf(stderr, "invalid table file format\n");
        exit(1);
    }
    
    //fprintf(stdout, "%s\n", key);
    
    for (i=0; i<8; i++)
    {
        temp[0] = key[i*2];
        temp[1] = key[i*2+1];
        hex_key[i] = strtoul(temp, NULL, 16);
    }
    
    /*
     for (i=0; i<8; i++)
     {
     printf("%02x\n", hex_key[i]);
     }
     */
    
    
    for (i=0; i<28; i++)
    {
        if (( (hex_key[(pc1_values[i]-1)/8]) >> (7 - ((pc1_values[i]-1)%8)) ) & 0x01)
        {
            C[i/8] = C[i/8] | (0x01 << (7 - ((i)%8)));
        }
        if (( (hex_key[(pc1_values[i+28]-1)/8]) >> (7 - ((pc1_values[i+28]-1)%8)) ) & 0x01)
        {
            D[(i+4)/8] = D[(i+4)/8] | (0x01 << (7 - ((i+4)%8)));
        }
    }
    
    memcpy(T, C, 3);
    *(T+3) = *(C+3) | (*D);
    memcpy(T+4, D+1, 3);
    fprintf(stderr, "(C%d,D%d)=%02x%02x%02x%02x%02x%02x%02x\n", 0, 0, *T, *(T+1), *(T+2), *(T+3), *(T+4), *(T+5), *(T+6));
    
    
    for (i=0; i<16; i++)
    {
        
        for (j=0; j<v_values[i]; j++)
        {
            if ((( (C[0/8]) >> (7 - (0%8)) ) & 0x01))
            {
                for (k=0; k<27; k++)
                {
                    if ((( (C[(k+1)/8]) >> (7 - ((k+1)%8)) ) & 0x01))
                    {
                        C[k/8] = C[k/8] | (0x01 << (7 - ((k)%8)));
                    }
                    else
                    {
                        C[k/8] = C[k/8] & (~(0x01 << (7 - ((k)%8))));
                    }
                }
                
                C[27/8] = C[27/8] | (0x01 << (7 - ((27)%8)));
            }
            else
            {
                for (k=0; k<27; k++)
                {
                    if ((( (C[(k+1)/8]) >> (7 - ((k+1)%8)) ) & 0x01))
                    {
                        C[k/8] = C[k/8] | (0x01 << (7 - ((k)%8)));
                    }
                    else
                    {
                        C[k/8] = C[k/8] & (~(0x01 << (7 - ((k)%8))));
                    }
                }
                
                C[27/8] = C[27/8] & (~(0x01 << (7 - ((27)%8))));
            }
        }
        
        for (j=0; j<v_values[i]; j++)
        {
            if ((( (D[4/8]) >> (7 - (4%8)) ) & 0x01))
            {
                for (k=4; k<31; k++)
                {
                    if ((( (D[(k+1)/8]) >> (7 - ((k+1)%8)) ) & 0x01))
                    {
                        D[k/8] = D[k/8] | (0x01 << (7 - ((k)%8)));
                    }
                    else
                    {
                        D[k/8] = D[k/8] & (~(0x01 << (7 - ((k)%8))));
                    }
                }
                
                D[31/8] = D[31/8] | (0x01 << (7 - ((31)%8)));
            }
            else
            {
                for (k=4; k<31; k++)
                {
                    if ((( (D[(k+1)/8]) >> (7 - ((k+1)%8)) ) & 0x01))
                    {
                        D[k/8] = D[k/8] | (0x01 << (7 - ((k)%8)));
                    }
                    else
                    {
                        D[k/8] = D[k/8] & (~(0x01 << (7 - ((k)%8))));
                    }
                }
                
                D[31/8] = D[31/8] & ~(0x01 << (7 - ((31)%8)));
            }
        }
        
        memcpy(T, C, 3);
        *(T+3) = *(C+3) | (*D);
        memcpy(T+4, D+1, 3);
        fprintf(stderr, "(C%d,D%d)=%02x%02x%02x%02x%02x%02x%02x\n", i+1, i+1, *T, *(T+1), *(T+2), *(T+3), *(T+4), *(T+5), *(T+6));
        
        for (j=0; j<48; j++)
        {
            if ((( (T[(pc2_values[j]-1)/8]) >> (7 - ((pc2_values[j]-1)%8)) ) & 0x01))
            {
                keys[i][j/8] = keys[i][j/8] | (0x01 << (7 - ((j)%8)));
            }
        }
        
        fprintf(stderr, "k%d=%02x%02x%02x%02x%02x%02x\n", i+1, keys[i][0], keys[i][1], keys[i][2], keys[i][3], keys[i][4], keys[i][5]);
    }
    return 0;
}


int encrypt3(FILE *fp, FILE *fp_input, const char * key)
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
        encrypt_block(block_in, block_out, keys1, fp, flag);
        for(i=0; i<8; i++) block_in[i] = 0x00;
        decrypt_block(block_out, block_in, keys2, fp, flag);
        for(i=0; i<8; i++) block_out[i] = 0x00;
        encrypt_block(block_in, block_out, keys3, fp, flag);
        
        
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
