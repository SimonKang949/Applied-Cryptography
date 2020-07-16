//
//  encrypt.c
//  HW4
//
//  Created by Simon Kang on 3/11/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_line_format(FILE *fp, int * check_values, char * line_header, int len);




int encrypt_block(unsigned char * block_in, unsigned char * block_out, unsigned char keys[16][6], FILE *fp, int flag)
{
    int ip_values[64] = {0};
    int ip_inv_values[64] = {0};
    int e_values[48] = {0};
    int s_values[64] = {0};
    char header[3];
    int p_values[32] = {0};
    unsigned char* L = (unsigned char*)calloc(1,4);
    unsigned char* R = (unsigned char*)calloc(1,4);
    unsigned char* Expend_R = (unsigned char*)calloc(1,6);
    unsigned char* Shorten_R = (unsigned char*)calloc(1,4);
    unsigned char* old_L = (unsigned char*)calloc(1,4);
    
    int i = 0;
    int j = 0;
    int row = 0;
    int column = 0;
    
    
    if(check_line_format(fp, ip_values, (char *)"IP=", 64))
    {
        fprintf(stderr, "table file has invalid values.\n");
        return 1;
    }
    
    for(i=0; i<64; i++) {
        for(j=0; j<64; j++)
        {
            if(ip_values[j] == (i+1))
            {
                ip_inv_values[i] = j+1;
                break;
            }
        }
    }
    
    for(i=0; i<64; i++)
    {
        if ((( (block_in[(ip_values[i]-1)/8]) >> (7 - ((ip_values[i]-1)%8)) ) & 0x01))
        {
            block_out[i/8] = block_out[i/8] | (0x01 << (7 - ((i)%8)));
        }
        else
        {
            block_out[i/8] = block_out[i/8] & ~(0x01 << (7 - ((i)%8)));
        }
    }
    
    memcpy(L, block_out, 4);
    memcpy(R, block_out+4, 4);
    
    if (flag == 0)
    {
        fprintf(stderr, "(L0,R0)=%02x%02x%02x%02x%02x%02x%02x%02x\n", *L, *(L+1), *(L+2), *(L+3), *R, *(R+1), *(R+2), *(R+3) );
    }
    
    
    for (i=0; i<16; i++)
    {
        memcpy(old_L, L, 4);
        memcpy(L, R, 4);
        
        
        if(check_line_format(fp, e_values, (char *)"E=", 48))
        {
            fprintf(stderr, "table file has invalid values.\n");
            return 1;
        }
        
        for (j=0; j<48; j++)
        {
            if ((( (R[(e_values[j]-1)/8]) >> (7 - ((e_values[j]-1)%8)) ) & 0x01))
            {
                Expend_R[j/8] = Expend_R[j/8] | (0x01 << (7 - ((j)%8)));
            }
            else
            {
                Expend_R[j/8] = Expend_R[j/8] & (~(0x01 << (7 - ((j)%8))));
            }
        }
        
        for(j=0; j<6; j++)
        {
            Expend_R[j] ^= keys[i][j];
        }
        
        for (j=0; j<4; j++)
        {
            Shorten_R[j] = 0x00;
        }
        
        for (j=0; j<8; j++)
        {
            sprintf(header, "S%d=",j+1);
            
            if (check_line_format(fp, s_values, header, 64))
            {
                fprintf(stderr, "table file has invalid values.\n");
                return 1;
            }
            
            row = (2*(( (Expend_R[(j*6)/8]) >> (7 - ((j*6)%8)) ) & 0x01)) + (( (Expend_R[((j*6)+5)/8]) >> (7 - (((j*6)+5)%8)) ) & 0x01);
            column = (8*(( (Expend_R[((j*6)+1)/8]) >> (7 - (((j*6)+1)%8)) ) & 0x01)) + (4*(( (Expend_R[((j*6)+2)/8]) >> (7 - (((j*6)+2)%8)) ) & 0x01)) + (2*(( (Expend_R[((j*6)+3)/8]) >> (7 - (((j*6)+3)%8)) ) & 0x01)) + (( (Expend_R[((j*6)+4)/8]) >> (7 - (((j*6)+4)%8)) ) & 0x01);
            
            
            
            *(Shorten_R + j/2) |= ( s_values[ 16*row + column ] << (4 * ((j+1)%2)) );
            
        }
        
        if(check_line_format(fp, p_values, (char *)"P=", 32))
        {
            fprintf(stderr, "table file has invalid values.\n");
            return 1;
        }
        
        for (j=0; j<32; j++)
        {
            
            if ((( (Shorten_R[(p_values[j]-1)/8]) >> (7 - ((p_values[j]-1)%8)) ) & 0x01))
            {
                R[j/8] = R[j/8] | (0x01 << (7 - ((j)%8)));
            }
            else
            {
                R[j/8] = R[j/8] & ~(0x01 << (7 - ((j)%8)));
            }
        }
        
        for(j=0; j<4; j++)
        {
            R[j] = old_L[j] ^ R[j];
        }
        
        if(flag == 0) {
            fprintf(stderr, "(L%d,R%d)=%02x%02x%02x%02x%02x%02x%02x%02x\n", i+1, i+1, *L, *(L+1), *(L+2), *(L+3), *R, *(R+1), *(R+2), *(R+3) );
        }
        
    }
    
    
    unsigned char* temp_block = (unsigned char*)malloc(8);
    memcpy(temp_block, R, 4);
    memcpy(temp_block+4, L, 4);
    for(i=0; i<64; i++)
    {
        if ((( (temp_block[(ip_inv_values[i]-1)/8]) >> (7 - ((ip_inv_values[i]-1)%8)) ) & 0x01))
        {
            block_out[i/8] = block_out[i/8] | (0x01 << (7 - ((i)%8)));
        }
        else
        {
            block_out[i/8] = block_out[i/8] & ~(0x01 << (7 - ((i)%8)));
        }
    }
    
    
    return 0;
}


int DES_encrypt(FILE *fp, FILE *fp_input, const char * key)
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
    unsigned char keys[16][6] = {{0}};
    int size = 0;
    int flag = 0;
    unsigned char * block_in = (unsigned char *)calloc(1, 8);
    unsigned char * block_out = (unsigned char *)calloc(1, 8);
    
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
    
    
    while((size = (int)fread(block_in, 1, 8, fp_input)))
    {
        if((*block_in == '\n') && (size == 1))
        {
            continue;
        }
        encrypt_block(block_in, block_out, keys, fp, flag);
        
        printf("%c%c%c%c%c%c%c%c", *block_out, *(block_out+1), *(block_out+2), *(block_out+3), *(block_out+4), *(block_out+5), *(block_out+6), *(block_out+7) );
        
        flag = 1;
        for(i=0; i<8; i++)
        {
            block_in[i] = 0x00;
            block_out[i] = 0x00;
        }
    }
    
    
    //printf("this is function DES_encrypt\n");
    return 0;
}
