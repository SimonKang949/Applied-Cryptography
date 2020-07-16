//
//  x3.c
//  HW7
//
//  Created by Simon Kang on 4/27/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int x3(FILE * input_file)
{
    double threshold[10];
    
    threshold[0] = 3.8415;
    threshold[1] = 7.8147;
    threshold[2] = 14.0671;
    threshold[3] = 24.9958;
    threshold[4] = 44.9853;
    threshold[5] = 82.5287;
    threshold[6] = 154.3015;
    threshold[7] = 293.2478;
    threshold[8] = 564.6961;
    threshold[9] = 1098.5208;
    
    double amount_n = 0;
    int buffer = 0;
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    double x3 = 0;
    
    int m = 0;
    int k = 0;
    int check = 0;
    int index = 0;
    int i = 0;
    int j = 0;
    int location = 0;
    
    fseek(input_file, 0 ,SEEK_SET);
    buffer = fgetc(input_file);
    
    FILE * temp_file = NULL;
    
    temp_file = fopen("x3.temp", "wb");
    
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
    temp_file = fopen("x3.temp", "rb");
    
    amount_n = count*8;
    
    for (m=1; m<=10; m++)
    {
        k = amount_n/m;
        if (k >= (5*pow(2, m)))
        {
            continue;
        }
        else
        {
            
            m--;
            break;
        }
    }
    
    if(m == 11)
    {
        m = 10;
    }
    
    k = amount_n/m;
    printf("n = %d\n", (int)amount_n);
    printf("m = %d\n", m);
    printf("k = %d\n", k);
    
    index = (int)pow(2, m);
    
    double n_occurrences[index];
    
    for (i=0; i<index; i++)
    {
        n_occurrences[i] = 0;
    }
    
    
    buffer = 0;
    int buff[8*m];
    
    for (i=0; i<8*m; i++)
    {
        buff[i] = 0;
    }
    
    fseek(temp_file, 0, SEEK_SET);
    buffer = fgetc(temp_file);
    
    int flag = 0;
    count = 0;
    
    while (buffer != EOF)
    {
        count++;
        check = 0;
        
        if (flag == 0)
        {
            for (i=0; i<8*m; i++)
            {
                buff[i] = 0;
            }
        }
        
        
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
        
        
        
        if (count == m)
        {
            count = 0;
            flag = 0;
            for (i=0; i<8; i++)
            {
                check = 0;
                for (j=0; j<m; j++)
                {
                    if (buff[i*m+j] == 1)
                    {
                        check += pow(2, m-j-1);
                    }
                }
                //printf("check is %d\n", check);
                n_occurrences[check]++;
            }
        }
         
        
         
         buffer = fgetc(temp_file);
        
    }
    
    fclose(temp_file);
    
    //printf("count is %d\n", count);
    
    
    count *= 8;
    count1 = count/m;
    
    if (count >= m)
    {
        for (i=0; i<count1; i++)
        {
            check = 0;
            for (j=0; j<m; j++)
            {
                if (buff[i*m+j] == 1)
                {
                    check += pow(2, m-j-1);
                }
            }
            //printf("check is %d\n", check);
            n_occurrences[check]++;
        }
    }
    
     for (i=0; i<index; i++)
     {
         printf("n");
         location = m-1;
         while (location >= 0)
         {
             if (((i>>(location)) & 0x01) == 0)
             {
                 printf("0");
             }
             else if(((i>>(location)) & 0x01) == 1)
             {
                 printf("1");
             }
             location--;
         }
         printf(" = %d\n",(int)n_occurrences[i]);
     
     }
    
    double sum = 0;
    
    
    for (i=0; i<index; i++)
    {
        sum += pow(n_occurrences[i], 2);
    }
    
    x3 = (pow(2, m) * sum / k) - k;
    
    printf("x3 = %f\n", x3);
    
    printf("pass/fail = ");
    if (x3 <= threshold[m-1])
    {
        printf("pass\n");
    }
    else
    {
        printf("fail\n");
    }
    
    
    //printf("this is function x3\n");
    return 0;

}
