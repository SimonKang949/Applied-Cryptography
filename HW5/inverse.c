//
//  inverse.c
//  HW5
//
//  Created by Simon Kang on 4/1/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_hex(char check);
unsigned char multiply(unsigned char p1, unsigned char p2);
void modprod_operation(unsigned char * p1, unsigned char * p2, unsigned char product[4]);


int generate_inverse(unsigned char poly[4], unsigned char inv_table[256], unsigned char inv_poly[4])
{
    unsigned char rem[6][5] = { { 0x01, 0x00, 0x00, 0x00, 0x01 }, { 0x00, poly[0], poly[1], poly[2], poly[3] } };
    unsigned char quo[6][4] = { { 0 } };
    unsigned char aux[6][4] = { { 0 }, { rem[0][1], rem[0][2], rem[0][3], rem[0][4] } };
    int i = 0;
    int j = 0;
    
    printf("i=1, rem[i]={%02x}{%02x}{%02x}{%02x}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}\n", rem[0][1], rem[0][2], rem[0][3], rem[0][4]);
    printf("i=2, rem[i]={%02x}{%02x}{%02x}{%02x}, quo[i]={00}{00}{00}{00}, aux[i]={%02x}{%02x}{%02x}{%02x}\n", poly[0], poly[1], poly[2], poly[3], aux[1][0], aux[1][1], aux[1][2], aux[1][3]);
    
    for(i=2; i<6; i++)
    {
        unsigned char temp_math[6-i];
        quo[i][2] = multiply(inv_table[ rem[i-1][i-1] ], rem[i-2][i-2]);
        
        for(j=0; j<(6-i); j++)
        {
            temp_math[j] = rem[i-2][j+i-1] ^ multiply( rem[i-1][j+i], quo[i][2] );
        }
        
        
        if(i<5)
        {
            temp_math[5-i] = rem[i-2][4];
            quo[i][3] = multiply(inv_table[ rem[i-1][i-1] ], temp_math[0]);
        }
        else
        {
            quo[i][3] = multiply(inv_table[ rem[i-1][i-1] ], temp_math[0]^0x01);
            rem[i][i-1] = 0x01;
        }
        
        
        for(j=i; j<5; j++)
        {
            rem[i][j] = temp_math[j-i+1] ^ multiply( rem[i-1][j], quo[i][3] );
        }
        
        
        modprod_operation(quo[i], aux[i-1], aux[i]);
        for(j=0; j<4; j++)
        {
            aux[i][j] ^= aux[i-2][j];
        }
        
        
        printf("i=%d, rem[i]={%02x}{%02x}{%02x}{%02x}, quo[i]={%02x}{%02x}{%02x}{%02x}, aux[i]={%02x}{%02x}{%02x}{%02x}\n", i+1, rem[i][1], rem[i][2], rem[i][3], rem[i][4], quo[i][0], quo[i][1], quo[i][2], quo[i][3], aux[i][0], aux[i][1], aux[i][2], aux[i][3]);
        
        /*
        if(i != 5 && rem[i][i] == 0x00)
        {
            printf("{%02x}{%02x}{%02x}{%02x} does not have a multiplicative inverse.\n", poly[0], poly[1], poly[2], poly[3]);
            exit(0);
        }
         */
    }
    
    for(i=0; i<4; i++)
    {
        inv_poly[i] = aux[5][i];
    }
    
    printf("Multiplicative inverse of {%02x}{%02x}{%02x}{%02x} is {%02x}{%02x}{%02x}{%02x}\n", poly[0], poly[1], poly[2], poly[3], inv_poly[0], inv_poly[1], inv_poly[2], inv_poly[3]);
    
    
    return 0;
}


int inverse(const char * poly)
{
    unsigned char * poly1= (unsigned char*)calloc(1,4);
    unsigned char * inv_poly = (unsigned char*)calloc(1,4);
    unsigned char * inv_table = (unsigned char*)calloc(1,256);
    
    unsigned char * hard_table = (unsigned char *)"00018df6cb527bd1e84f29c0b0e1e5c774b4aa4b992b605f583ffdccff40eeb23a6e5af1554da8c9c10a98153044a2c22c45926cf3396642f235206f77bb59191dfe37672d31f569a764ab135425e909ed5c05ca4c2487bf183e22f051ec6117165eafd349a63643f44791df3393213b79b7978510b5ba3cb670d006a1fa8182837e7f809673be569b9e95d9f702b9a4de6a326dd88a84722a149f88f9dc899afb7c2ec38fb8654826c8124acee7d2620ce01fef11757871a58e763dbdbc86570b282fa3dad4e40fa92753041bfcace67a07ae63c5dbe2ea948bc4d59df8906bb10dd6ebc60ecfad084ed7e35d501eb35b2338346846038cdd9c7da0cd1a411c";
    
    char temp_values[3];
    int i = 0;
    
    
    for(i=0; i<256; i++)
    {
        temp_values[0] = hard_table[i*2];
        temp_values[1] = hard_table[i*2+1];
        temp_values[2] = ' ';
        inv_table[i] = strtol(temp_values, NULL, 16);
    }
    
    
    if(strlen(poly) != 8)
    {
        fprintf(stderr, "bad poly\n");
        exit(1);
    }
    
    
    for(i=0; i<4; i++)
    {
        if(check_hex(poly[i*2]) || check_hex(poly[i*2+1]))
        {
            fprintf(stderr, "invalid poly.\n");
            exit(1);
        }
        
        temp_values[0] = poly[i*2];
        temp_values[1] = poly[i*2+1];
        temp_values[2] = ' ';
        poly1[i] = strtol(temp_values, NULL, 16);
    }
    
    
    generate_inverse(poly1, inv_table, inv_poly);
    
    //printf("%s\n", poly);
    //printf("this is function inverse\n");
    return 0;
}
