//
//  primes.c
//  HW6
//
//  Created by Simon Kang on 4/12/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


int print_byte(unsigned int value)
{
    value = htonl(value);
    fwrite(&value, sizeof(uint32_t), 1, stdout);
    return 0;
}


int check(char * primes, unsigned int i)
{
    unsigned char mask = 1;
    mask = mask << (8-(i%8)-1);
    
    if ((primes[i/8] & mask) == mask)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int set(char * primes, unsigned int i)
{
    unsigned char mask = 1;
    mask = mask << (8-(i%8)-1);
    
    if ((primes[i/8] & mask) == mask)
    {
        primes[i/8] = primes[i/8] ^ mask;
    }
    
    
    
    return 0;
}


int Sieve_of_Eratosthenes(unsigned int maxval)                       //this algorithm refers to Sieve of Eratosthenes on HW6 webpage
{
    //int buffer_num = ceil(maxval/8);
    int buffer_num = 0;
    
    if (maxval%8 == 0)
    {
        buffer_num = maxval/8;
    }
    else if (maxval%8 != 0)
    {
        buffer_num = maxval/8 + 1;
    }
    
    char * primes = (char *)calloc(buffer_num, sizeof(char));
    unsigned int i = 0;
    unsigned int j = 0;
    //unsigned char mask = 1;
    
    
    for (i=0; i<=buffer_num; i++)
    {
        primes[i]  = 0xff;
    }
    
    primes[0] = 0x3f;
    
    for (i=2; i*i<=maxval; i++)
    {
        j=i*i;
        while (j<=maxval)
        {
            //primes[j] = 0;
            //mask = 1;
            //mask = mask << (8-j%8-1);
            //primes[j/8] = primes[j/8] ^ mask;
            set(primes, j);
            j+=i;
        }
    }
    
    //fwrite(primes, buffer_num, 1, stdout);
    
    
    for (i=2; i<=maxval; i++)
    {
        
        if (check(primes, i))
        {
            print_byte(i);
        }
    }
    
    
    return 0;
}



int primes(unsigned int maxval)
{
    
    print_byte(maxval);
    
    Sieve_of_Eratosthenes(maxval);
    
    
    //printf("this is function primes\n");
    //printf("maxval is %d\n", maxval);
    return 0;
}
