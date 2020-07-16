//
//  x1.c
//  HW7
//
//  Created by Simon Kang on 4/26/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x1(FILE * input_file)
{
    double n[2] = {0};
    double amount_n = 0;
    int buffer = 0;
    int count1 = 0;
    int count2 = 0;
    double x1 = 0;
    
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
        
        buffer = fgetc(input_file);
    }
    
    amount_n = n[0] + n[1];
    printf("n = %d\n", (int)amount_n);
    printf("n0 = %d\n", (int)n[0]);
    printf("n1 = %d\n", (int)n[1]);
    x1 = ((n[0]-n[1])*(n[0]-n[1]))/amount_n;
    printf("x1 = %f\n", x1);
    printf("pass/fail = ");
    if (x1 <= 3.8415)
    {
        printf("pass\n");
    }
    else
    {
        printf("fail\n");
    }
    
    //printf("this is function x1\n");
    return 0;
}
