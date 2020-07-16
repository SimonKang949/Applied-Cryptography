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


int Sieve_of_Eratosthenes(unsigned int maxval)                       //this algorithm refers to Sieve of Eratosthenes on HW6 webpage
{
    //int buffer_num = ceil(maxval/8);
    //char * primes = (char *)calloc(buffer_num, sizeof(char));
    char * primes = (char *)calloc(maxval+1, sizeof(char));
    unsigned int i = 0;
    unsigned int j = 0;
    
    primes[0] = 0;
    primes[1] = 0;
    
    for (i=2; i<=maxval; i++)
    {
        primes[i] = 1;
    }
    
    for (i=2; i*i<=maxval; i++)
    {
        j=i*i;
        while (j<=maxval)
        {
            primes[j] = 0;
            j+=i;
        }
    }
    
    for (i=2; i<=maxval; i++)
    {
        if (primes[i] == 1)
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
