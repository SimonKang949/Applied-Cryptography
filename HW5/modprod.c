//
//  modprod.c
//  HW5
//
//  Created by Simon Kang on 4/1/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned char xtime(unsigned char x)
{
    return ((((x) << 1) ^ (((x) & 0x80) != 0 ? 0x1B : 0)) & 0xFF);
}

int hex_checking(char check)
{
    if (check >= '0' && check <= '9')
    {
        return 0;
    }
    else if (check >= 'a' && check <= 'f')
    {
        return 0;
    }
    else if (check >= 'A' && check <= 'F')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char multiply(unsigned char p1, unsigned char p2)
{
    
    unsigned char a = 0;
    unsigned char b = p2;
    int i=0;
    
    for (i=0 ; i < 8 ; i++)
    {
        if (p1%2 == 1) a ^= b;
        p1 /= 2;
        b = xtime(b);
    }
    return a;
}

void modprod_operation(unsigned char * p1, unsigned char * p2, unsigned char product[4])
{
    product[3] = multiply(p1[3],p2[3]) ^ multiply(p1[0],p2[2]) ^ multiply(p1[1],p2[1]) ^ multiply(p1[2],p2[0]);
    product[2] = multiply(p1[2],p2[3]) ^ multiply(p1[3],p2[2]) ^ multiply(p1[0],p2[1]) ^ multiply(p1[1],p2[0]);
    product[1] = multiply(p1[1],p2[3]) ^ multiply(p1[2],p2[2]) ^ multiply(p1[3],p2[1]) ^ multiply(p1[0],p2[0]);
    product[0] = multiply(p1[0],p2[3]) ^ multiply(p1[1],p2[2]) ^ multiply(p1[2],p2[1]) ^ multiply(p1[3],p2[0]);
}



int modprod(const char * poly1, const char * poly2)
{
    
    unsigned char * product = (unsigned char*)malloc(4);
    unsigned char p1[4];
    unsigned char p2[4];
    unsigned int i = 0;
    char temp_values[3];
    
    for(i=0; i<strlen(poly1); i++)
    {
        if(hex_checking(poly1[i]))
        {
            fprintf(stderr, "Not all values are hex in p1\n");
            exit(1);
        }
    }
    
    for(i=0; i<strlen(poly2); i++)
    {
        if(hex_checking(poly2[i]))
        {
            fprintf(stderr, "Not all values are hex in p2\n");
            exit(1);
        }
    }
    
    
    for(i=0; i<4; i++)
    {
        temp_values[0] = poly1[i*2];
        temp_values[1] = poly1[i*2+1];
        temp_values[2] = ' ';
        p1[i] = strtol(temp_values, NULL, 16);
        
        temp_values[0] = poly2[i*2];
        temp_values[1] = poly2[i*2+1];
        temp_values[2] = ' ';
        p2[i] = strtol(temp_values, NULL, 16);
    }
    
    
    modprod_operation(p1, p2, product);
    
    printf("{%c%c}{%c%c}{%c%c}{%c%c} CIRCLEX ", poly1[0], poly1[1], poly1[2], poly1[3], poly1[4], poly1[5], poly1[6], poly1[7]);
    printf("{%c%c}{%c%c}{%c%c}{%c%c} = ", poly2[0], poly2[1], poly2[2], poly2[3], poly2[4], poly2[5], poly2[6], poly2[7]);
    printf("{%02x}{%02x}{%02x}{%02x}\n", product[0], product[1], product[2], product[3]);
    
    //printf("p1 is: %s\n", poly1);
    //printf("p2 is: %s\n", poly2);
    //printf("this is function modprod\n");
    return 0;
}
