//
//  x5.c
//  HW7
//
//  Created by Simon Kang on 4/28/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int x5(FILE * input_file, int dval)
{
    double amount_n = 0;
    int buffer = 0;
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    int Ad = 0;
    double x5 = 0;
    
    fseek(input_file, 0 ,SEEK_SET);
    buffer = fgetc(input_file);
    
    FILE * temp_file = NULL;
    
    temp_file = fopen("x5.temp", "wb");
    
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
        count++;
        
        fputc(buffer, temp_file);
        
        buffer = fgetc(input_file);
    }
    
    fclose(temp_file);
    
    temp_file = NULL;
    temp_file = fopen("x5.temp", "rb");
    
    amount_n = count*8;
    
    char buff[(int)amount_n];
    
    int i = 0;
    int flag = 0;
    
    for (i=0; i<(int)amount_n; i++)
    {
        buff[i] = 0;
    }
    
    fseek(temp_file, 0, SEEK_SET);
    buffer = fgetc(temp_file);
    count = 0;
    while (buffer != EOF)
    {
        for (i=0; i<8; i++)
        {
            if (((buffer>>(7-i)) & 0x01) == 0)
            {
                buff[flag] = 0;
                flag++;
            }
            else if (((buffer>>(7-i)) & 0x01) == 1)
            {
                buff[flag] = 1;
                flag++;
            }
        }
        
        
        
        buffer = fgetc(temp_file);
        
    }
    
    count = 0;
    for (i=dval; i<amount_n; i++)
    {
        if (buff[i] != buff[i-dval])
        {
            Ad++;
        }
        count++;
    }
    
    //printf("i is %d\n", i);
    //printf("count is %d\n", count);
    
    printf("n = %d\n", (int)amount_n);
    printf("d = %d\n", dval);
    printf("A(d) = %d\n", Ad);
    
    x5 = (2 * (Ad - ((amount_n-dval)/2))) / sqrt(amount_n-dval);
    printf("x5 = %f\n", x5);
    
    printf("pass/fail = ");
    if (fabs(x5) <= 1.9600)
    {
        printf("pass\n");
    }
    else
    {
        printf("fail\n");
    }
    
    
    fclose(temp_file);
    //printf("this is function x5\n");
    //printf("dval is %d\n", dval);
    return 0;
}
