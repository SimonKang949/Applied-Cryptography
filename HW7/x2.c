//
//  x2.c
//  HW7
//
//  Created by Simon Kang on 4/26/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x2(FILE * input_file)
{
    double n[2] = {0};
    double n00 = 0;
    double n01 = 0;
    double n10 = 0;
    double n11 = 0;
    double amount_n = 0;
    int buffer = 0;
    int buffer2 = 0;
    int temp = 0;
    int count1 = 0;
    int count2 = 0;
    double x2 = 0;
    
    fseek(input_file, 0, SEEK_SET);
    buffer = fgetc(input_file);
    
    while (buffer != EOF)
    {
        if (count2 != 16)
        {
            printf("%02x", buffer);
            count1++;
            if (count1 % 16 == 0)
            {
                printf("\n");
                count2++;
            }
        }
     
     
        if (((buffer>>7) & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if(((buffer>>7) & 0x01) == 1)
        {
            n[1] += 1;
        }
     
        if (((buffer>>6) & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if(((buffer>>6) & 0x01) == 1)
        {
            n[1] += 1;
        }
        
        if (((buffer>>5) & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if(((buffer>>5) & 0x01) == 1)
        {
            n[1] += 1;
        }
        
        if (((buffer>>4) & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if(((buffer>>4) & 0x01) == 1)
        {
            n[1] += 1;
        }
        
        if (((buffer>>3) & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if(((buffer>>3) & 0x01) == 1)
        {
            n[1] += 1;
        }
        
        if (((buffer>>2) & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if(((buffer>>2) & 0x01) == 1)
        {
            n[1] += 1;
        }
        
        if (((buffer>>1) & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if(((buffer>>1) & 0x01) == 1)
        {
            n[1] += 1;
        }
        
        if ((buffer & 0x01) == 0)
        {
            n[0] += 1;
        }
        else if((buffer & 0x01) == 1)
        {
            n[1] += 1;
        }
        
        
        if (((buffer>>6) & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if(((buffer>>6) & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if(((buffer>>6) & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if(((buffer>>6) & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        if (((buffer>>5) & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if(((buffer>>5) & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if(((buffer>>5) & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if(((buffer>>5) & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        if (((buffer>>4) & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if(((buffer>>4) & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if(((buffer>>4) & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if(((buffer>>4) & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        if (((buffer>>3) & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if(((buffer>>3) & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if(((buffer>>3) & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if(((buffer>>3) & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        if (((buffer>>2) & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if(((buffer>>2) & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if(((buffer>>2) & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if(((buffer>>2) & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        if (((buffer>>1) & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if(((buffer>>1) & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if(((buffer>>1) & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if(((buffer>>1) & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        if (((buffer>>0) & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if(((buffer>>0) & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if(((buffer>>0) & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if(((buffer>>0) & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        
        buffer2 = fgetc(input_file);
        if (buffer2 == EOF)
        {
            break;
        }
        
        temp = ((buffer << 1) & 0x02) | ((buffer2 >> 7) & 0x01);
        if ((temp & 0x03) == 0x00)
        {
            n00 += 1;
        }
        else if((temp & 0x03) == 0x01)
        {
            n01 += 1;
        }
        else if((temp & 0x03) == 0x02)
        {
            n10 += 1;
        }
        else if((temp & 0x03) == 0x03)
        {
            n11 += 1;
        }
        
        buffer = buffer2;
    }
    amount_n = n[0] + n[1];
    printf("n = %d\n", (int)amount_n);
    printf("n0 = %d\n", (int)n[0]);
    printf("n1 = %d\n", (int)n[1]);
    
    printf("n00 = %d\n", (int)n00);
    printf("n01 = %d\n", (int)n01);
    printf("n10 = %d\n", (int)n10);
    printf("n11 = %d\n", (int)n11);
    
    x2 = 4*((n00*n00)+(n01*n01)+(n10*n10)+(n11*n11))/(amount_n-1)-2*((n[0]*n[0])+(n[1]*n[1]))/amount_n+1;
    printf("x2 = %f\n", x2);
    
    printf("pass/fail = ");
    if (x2 <= 5.9915)
    {
        printf("pass\n");
    }
    else
    {
        printf("fail\n");
    }
    
    //printf("this is function x2\n");
    return 0;
    
}
