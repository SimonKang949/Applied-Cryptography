//
//  main.c
//  HW6
//
//  Created by Simon Kang on 4/12/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

int primes(unsigned int maxval);
int trialdiv(const char * number, FILE * primesfile);
int millerrabin(const char * number, const char * maxitr, FILE * primesfile);
int rndsearch(const char * numbits, const char * maxitr, FILE * primesfile, FILE * rndfile);
unsigned char * maurer(const char * numbits, FILE * primesfile, FILE * rndfile, BIGNUM * bn_num, int level);

int main(int argc, const char * argv[])
{
    //printf("%f\n", pow(2, 24));
    unsigned int maxval = 0;
    int i = 0;
    const char * number = NULL;
    FILE * primesfile = NULL;
    const char * maxitr = NULL;
    const char * numbits = NULL;
    FILE * rndfile = NULL;
    BIGNUM * bn_num = BN_new();
    
    
    
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
        
        else if (strncmp(argv[1], "trialdiv", 8) == 0)
        {
            if (argc == 4)
            {
                for (i=2; i<=3; i++)
                {
                    if (strncmp(argv[i], "-n=", 3) == 0)
                    {
                        number = argv[i]+3;
                    }
                    if (strncmp(argv[i], "-p=", 3) == 0)
                    {
                        primesfile = fopen(argv[i]+3, "rb");
                        if (primesfile == NULL)
                        {
                            fprintf(stderr, "primesfile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                trialdiv(number, primesfile);
                fclose(primesfile);
                
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "millerrabin", 11) == 0)
        {
            if (argc == 5)
            {
                for (i=2; i<=4; i++)
                {
                    if (strncmp(argv[i], "-n=", 3) == 0)
                    {
                        number = argv[i]+3;
                    }
                    if (strncmp(argv[i], "-t=", 3) == 0)
                    {
                        maxitr = argv[i]+3;
                    }
                    if (strncmp(argv[i], "-p=", 3) == 0)
                    {
                        primesfile = fopen(argv[i]+3, "rb");
                        if (primesfile == NULL)
                        {
                            fprintf(stderr, "primesfile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                printf("n = %s\n", number);
                millerrabin(number, maxitr, primesfile);
                fclose(primesfile);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        else if (strncmp(argv[1], "rndsearch", 9) == 0)
        {
            if (argc == 6)
            {
                for (i=2; i<=5; i++)
                {
                    if (strncmp(argv[i], "-k=", 3) == 0)
                    {
                        numbits = argv[i]+3;
                    }
                    if (strncmp(argv[i], "-t=", 3) == 0)
                    {
                        maxitr = argv[i]+3;
                    }
                    if (strncmp(argv[i], "-p=", 3) == 0)
                    {
                        primesfile = fopen(argv[i]+3, "rb");
                        if (primesfile == NULL)
                        {
                            fprintf(stderr, "primesfile does not exist\n");
                            exit(1);
                        }
                    }
                    if (strncmp(argv[i], "-r=", 3) == 0)
                    {
                        rndfile = fopen(argv[i]+3, "rb");
                        if (primesfile == NULL)
                        {
                            fprintf(stderr, "rndfile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                rndsearch(numbits, maxitr, primesfile, rndfile);
                fclose(primesfile);
                fclose(rndfile);
                
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "maurer", 6) == 0)
        {
            if (argc == 5)
            {
                for (i=2; i<=4; i++)
                {
                    if (strncmp(argv[i], "-k=", 3) == 0)
                    {
                        numbits = argv[i]+3;
                    }
                    if (strncmp(argv[i], "-p=", 3) == 0)
                    {
                        primesfile = fopen(argv[i]+3, "rb");
                        if (primesfile == NULL)
                        {
                            fprintf(stderr, "primesfile does not exist\n");
                            exit(1);
                        }
                    }
                    if (strncmp(argv[i], "-r=", 3) == 0)
                    {
                        rndfile = fopen(argv[i]+3, "rb");
                        if (primesfile == NULL)
                        {
                            fprintf(stderr, "rndfile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                maurer(numbits, primesfile, rndfile, bn_num, 0);
                fclose(primesfile);
                fclose(rndfile);
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
