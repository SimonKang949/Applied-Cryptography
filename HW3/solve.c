//
//  solve.c
//  HW3
//
//  Created by Simon Kang on 2/23/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kasiski(int file_len, char * file_buffer)
{
    int check_len = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int flag = 0;
    int check = 0;
    
    for (check_len=4; check_len>0; check_len++)
    {
        char * ini_str = malloc(check_len);
        char * comp_str = malloc(check_len);
        
        flag = 1;
        
        for (i =0; i<file_len - check_len; i++)
        {
            strncpy(ini_str, &file_buffer[i], check_len);
            
            for (k=0; k<check_len; k++)
            {
                if (ini_str[k]<97 || ini_str[k]>122)
                {
                    check = 1;
                }
            }
            
            if (check == 1)
            {
                check = 0;
                continue;
            }
            
            
            for (j=i+1; j<file_len-check_len; j++)
            {
                strncpy(comp_str, &file_buffer[j], check_len);
                if (strncmp(ini_str, comp_str, check_len) == 0)
                {
                    flag = 0;
                    fprintf(stdout, "len=%d, i=%d, j=%d, j-i=%d, %s\n", check_len, i, j, j-i, ini_str);
                }
            }
        }
        if (flag == 1)
        {
            fprintf(stdout, "len=%d, no more matches\n", check_len);
            break;
        }
        
        
    }
    
    
    //printf("this is function kasiski\n");
    return 0;
}

int average_index_of_coincidence(int file_len, char * file_buffer, int len)
{
    int alphabet_count[26];
    int count = 0;
    int i = 0;
    double kp = 0.0658;
    
    double IC, EIC = 0;
    
    for(i=0; i<26; i++)
    {
        alphabet_count[i] = 0;
    }
    
    count = 0;
    
    for (i=0; i<file_len; i++)
    {
        if (file_buffer[i]>=97 && file_buffer[i]<=122)
        {
            count++;
            alphabet_count[file_buffer[i]-97]++;
        }
    }
    
    printf("L=%d\n", count);
    for (i=0; i<26; i++)
    {
        printf("f('%c')=%d\n", 97+i, alphabet_count[i]);
    }
    
    for (i=0; i<26; i++)
    {
        IC += alphabet_count[i]*(alphabet_count[i]-1);
    }
    
    IC /= count*(count-1);
    
    printf("IC=%.9f\n", IC);
    
    for (i=1; i<len+1; i++)
    {
        EIC = ( kp * (count - i) / (i * (count - 1)) );
        EIC += 1.0*( ((double)1/26) * ((double)(i - 1) / i) * ((float)count / (count - 1)) );
        
        if(i != 1)
        {
            printf("t=%d, E(IC)=%.9f\n", i, EIC);
        }
        else
        {
            printf("t=%d, E(IC)=%.4f\n", i, kp);
        }
    }
    
    
    //printf("this is function average index of coincidence\n");
    return 0;
}

int auto_correlation(int file_len, char * file_buffer, int len)
{
    int i = 0;
    int j = 0;
    int count = 0;
    
    for (i=1; i<len+1; i++)
    {
        count = 0;
        for (j=0; j<file_len-i; j++)
        {
            if (file_buffer[j] >= 97 && file_buffer[j] <= 122)
            {
                if (file_buffer[j] == file_buffer[j+i])
                {
                    count++;
                }
            }
        }
        
        printf("t=%d, count=%d\n", i, count);
        
    }
    
    
    //printf("this is function auto-correlation\n");
    return 0;
}



int solve(int len, FILE * fp)
{
    int file_len = 0;
    
    fseek(fp, 0, SEEK_END);
    file_len = (int)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char * file_buffer = malloc(file_len);
    
    fread(file_buffer, 1, file_len, fp);
    
    printf("Kasiski Method\n");
    printf("==============\n");
    kasiski(file_len, file_buffer);
    printf("\n");
    
    printf("Average Index of Coincidence\n");
    printf("============================\n");
    average_index_of_coincidence(file_len, file_buffer, len);
    printf("\n");
    
    printf("Auto-correlation Method\n");
    printf("=======================\n");
    auto_correlation(file_len, file_buffer, len);
    printf("\n");
    
    //printf("this is function solve\n");
    fclose(fp);
    return 0;
}

