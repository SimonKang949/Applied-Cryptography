//
//  main.c
//  HW6
//
//  Created by Simon Kang on 4/12/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int primes(unsigned int maxval);


int main(int argc, const char * argv[])
{
    //printf("%f\n", pow(2, 24));
    unsigned int maxval = 0;
    
    
    if (argc<2)
    {
        fprintf(stderr, "Command Error\n");
        exit(1);
        
    }
    else
    {
        if (strncmp(argv[1], "primes", 6) == 0)
        {
            if (argc == 3)
            {
                if (strncmp(argv[2], "-n=", 3) == 0)
                {
                    maxval = atoi(argv[2]+3);
                    
                    if (maxval<2 || maxval>16777216)
                    {
                        fprintf(stderr, "the maxval should be between 2 to 2^24\n");
                        exit(1);
                    }
                    
                    primes(maxval);
                }
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
    }
    
    
    
    
    
    
    
    //printf("Hello, World!\n");
    return 0;
}
