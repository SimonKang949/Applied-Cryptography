//
//  x4.c
//  HW7
//
//  Created by Simon Kang on 4/28/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int x4(FILE * input_file)
{
    double threshold[10];
    
    threshold[0] = 5.9915;
    threshold[1] = 9.4877;
    threshold[2] = 12.5916;
    threshold[3] = 15.5073;
    threshold[4] = 18.3070;
    threshold[5] = 21.0261;
    threshold[6] = 23.6848;
    threshold[7] = 26.2962;
    threshold[8] = 28.8693;
    threshold[9] = 31.4104;
    
    double amount_n = 0;
    int buffer = 0;
    int count = 0;
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;
    double x4 = 0;
    
    int k = 0;
    int i = 0;
    int j = 0;
    
    int flag = 0;
    
    fseek(input_file, 0 ,SEEK_SET);
    buffer = fgetc(input_file);
    
    FILE * temp_file = NULL;
    
    temp_file = fopen("x4.temp", "wb");
    
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
    temp_file = fopen("x4.temp", "rb");
    
    amount_n = count*8;
    
    
    for (i=1; i<12; i++)
    {
        if (((int)amount_n-i+3)/pow(2, (i+2)) >= 5)
        {
            continue;
        }
        else
        {
            i--;
            break;
        }
        
    }
    
    if (i == 12)
    {
        i = 11;
    }
    
    k = i;
    
    printf("n = %d\n", (int)amount_n);
    printf("k = %d\n", k);
    
    
    double e = 0;
    double B[k];
    double G[k];
    
    for (i=0; i<k; i++)
    {
        B[i] = 0;
        G[i] = 0;
    }
    
    char buff[(int)amount_n];
    
    for (i=0; i<amount_n; i++)
    {
        buff[i] = 2;
    }
    
    fseek(temp_file, 0, SEEK_SET);
    buffer = fgetc(temp_file);
    
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
    
    fclose(temp_file);
    
    //printf("flag is %d\n", flag);
    //printf("8n is %d\n", (int)amount_n*8);
    
    count0 = 0;
    count1 = 0;
    
    
    //统计B和G的个数
    for (i=0; i<amount_n; i++)
    {
        if (buff[i] == 1)
        {
            count1++;
            
            if (i+1 == amount_n-1)
            {
                if (buff[i+1] == 0)
                {
                    if (count1 <= k)
                    {
                        B[count1-1]++;
                        count1 = 0;
                    }
                    else if (count1 > k)
                    {
                        count1 = 0;
                    }
                    
                    G[0]++;
                    break;
                }
                
                else if (buff[i+1] ==1)
                {
                    count1++;
                    if (count1 <= k)
                    {
                        B[count1-1]++;
                        count1 = 0;
                    }
                    else if (count1 > k)
                    {
                        count1 = 0;
                    }
                    break;
                }
            }
            
            if (buff[i+1] == 0)
            {
                if (count1 <= k)
                {
                    B[count1-1]++;
                    count1 = 0;
                }
                else if (count1 > k)
                {
                    count1 = 0;
                }
            }
            else if (buff[i+1] == 1)
            {
                continue;
            }
        }
        
        
        else if (buff[i] == 0)
        {
            count0++;
            
            if (i+1 == amount_n-1)
            {
                if (buff[i+1] == 1)
                {
                    if (count0 <= k)
                    {
                        G[count0-1]++;
                        count0 = 0;
                    }
                    else if (count0 > k)
                    {
                        count0 = 0;
                    }
                    
                    B[0]++;
                    break;
                }
                else if(buff[i+1] == 0)
                {
                    count0++;
                    if (count0 <= k)
                    {
                        G[count0-1]++;
                        count0 = 0;
                    }
                    else if (count0 > k)
                    {
                        count0 = 0;
                    }
                    
                    break;
                }
            }
            
            if (buff[i+1] == 1)
            {
                if (count0 <= k)
                {
                    G[count0-1]++;
                    count0 = 0;
                }
                else if (count0 > k)
                {
                    count0 = 0;
                }
            }
            else if (buff[i+1] == 0)
            {
                continue;
            }
        }
    }

    x4 = 0;
    
    for (i=1; i<=k; i++)
    {
        e = (amount_n-i+3)/pow(2, i+2);
        printf("e%d = %f\n", i, e);
        printf("B%d = %d\n", i, (int)B[i-1]);
        printf("G%d = %d\n", i, (int)G[i-1]);
        
        x4 += (pow((B[i-1]-e), 2)/e) + (pow((G[i-1]-e), 2)/e);
    }
    
    printf("x4 = %f\n", x4);
    printf("pass/fail = ");
    
    if (x4 <= threshold[k-2])
    {
        printf("pass\n");
    }
    else
    {
        printf("fail\n");
    }
    
    //printf("this is function x4\n");
    return 0;
}
