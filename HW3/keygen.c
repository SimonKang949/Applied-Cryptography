//
//  keygen.c
//  HW3
//
//  Created by Simon Kang on 2/23/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/md5.h>


int random_integer(const char *pphrase, int period, unsigned char * key_buff)                    //this function refers to the hw2 webpage and my hw2.
{
    unsigned char md5_buf[MD5_DIGEST_LENGTH];
    int len = strlen(pphrase) + 2 + MD5_DIGEST_LENGTH;
    char *s = malloc(len + 1);
    int i = 0;
    
    int key_size;
    
    MD5((unsigned char*)pphrase, strlen(pphrase), md5_buf);
    
    while(period > 0) {
        
        sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, (unsigned char*)pphrase);
        memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
        MD5((unsigned char*)s, len, md5_buf);
        
        if (period-8 >= 0)
        {
            period-=8;
            key_size = 8;
        }
        else
        {
            key_size = period;
            period = 0;
        }
        
        memcpy(key_buff, md5_buf, key_size);
        key_buff += key_size;
        
        if (++i == 100) {
            i = 0;
        }
    }
    
    free(s);
    
    
    
    //printf("this is function random_integer\n");
    return 0;
}

unsigned int cal_random_number(unsigned char *key_buff, int i)
{
    return ((key_buff[i - 3] << 24) + (key_buff[i - 2] << 16) + (key_buff[i - 1] << 8) + (key_buff[i]));
}


int keygen(const char * pphrase, int period)
{
    unsigned char key_buff[200 * period * sizeof (char)];
    int random_number[period * sizeof (int)];
    char alphabet_table[26];
    
    random_integer(pphrase, 200*period, key_buff);
    
    int i = 0;
    int j = 0;
    unsigned int L = 0;
    unsigned int R = 0;
    unsigned int X = 0;
    int count = 0;
    char temp = '\0';
    
    for (i = 0; i < 200 * period; i++)
    {
        if ((i + 1) % 4 == 0)
        {
            random_number[count] = cal_random_number(key_buff, i);
            count++;
        }
    }
    
    count = 0;
    
    for (i=0; i<period; i++)                                                          //the following algorithm refers to the hw3 webpage.
    {
        for(j=0; j<26; j++)
        {
            alphabet_table[j] = 97+j;
        }
        
        for (j=1; j<=2; j++)
        {
            L = 26;
            while (L > 1)
            {
                X = random_number[count++];
                R = X % L;
                if (R != (L-1))
                {
                    temp = alphabet_table[R];
                    alphabet_table[R] = alphabet_table[L-1];
                    alphabet_table[L-1] = temp;
                }
                L = L - 1;
            }
        }
        
        for (j=0; j<26; j++)
        {
            fprintf(stdout, "%c", alphabet_table[j]);
        }
        printf("\n");
    }
    
    
    
    //printf("this is function keygen\n");
    return 0;
}
