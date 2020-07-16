//
//  rndsearch.c
//  HW6
//
//  Created by Simon Kang on 4/15/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <arpa/inet.h>

int trialdiv_rnd(const char * number, FILE * primesfile)
{
    //printf("number is %s\n", number);
    
    
    BIGNUM * bn_maxval = BN_new();
    BIGNUM * bn_factor = BN_new();
    BIGNUM * bn_num = BN_new();
    BIGNUM * bn_remember = BN_new();
    BIGNUM * bn_square = BN_new();
    BN_CTX * ctx = BN_CTX_new();
    
    unsigned char maxval[4];
    unsigned char factor[4];
    
    BN_dec2bn(&bn_num, number);
    
    fseek(primesfile, 0 ,SEEK_SET);
    fread(maxval, 1, 4, primesfile);
    //fwrite(maxval, 4, 1, stdout);
    
    BN_bin2bn(maxval, 4, bn_maxval);
    
    
    while (!feof(primesfile))
    {
        fread(factor, 1, 4, primesfile);
        
        BN_bin2bn(factor, 4, bn_factor);
        BN_mod(bn_remember, bn_num, bn_factor, ctx);
        if(BN_is_zero(bn_remember) && BN_cmp(bn_num, bn_factor) != 0)
        {
            printf("  n is composite by trial division (mod %s = 0)\n", BN_bn2dec(bn_factor));
            return 1;
        }
    }
    
    BN_sqr(bn_square, bn_maxval, ctx);
    
    if(BN_cmp(bn_square, bn_num) == 0)
    {
        printf("  n passes trial division test (not enough primes)\n");
    }
    else
    {
        printf("  n passes trial division test\n");
    }
    
    //printf("the number is %d\n", number);
    //printf("this is function trialdiv\n");
    return 0;
}


int millerrabin_rnd(const char * number, const char * maxitr, FILE * primesfile)         //the function refers to the miller-rabin algorithm on the HW6 webpage
{
    //printf("number is %s\n", number);
    
    BIGNUM * bn_num = BN_new();
    BIGNUM * bn_r = BN_new();
    BIGNUM * bn_s = BN_new();
    BIGNUM * bn_one = BN_new();
    BIGNUM * bn_two = BN_new();
    BIGNUM * bn_rem = BN_new();
    BIGNUM * bn_n_minus_one = BN_new();
    BN_CTX * ctx = BN_CTX_new();
    
    BN_dec2bn(&bn_one, "1");
    BN_dec2bn(&bn_two, "2");
    
    BN_dec2bn(&bn_num, number);
    BN_sub(bn_r, bn_num, bn_one);
    BN_sub(bn_n_minus_one, bn_num, bn_one);
    
    BN_zero(bn_s);
    while (!BN_is_odd(bn_r))
    {
        BN_add(bn_s, bn_s, bn_one);
        BN_div(bn_r, bn_rem, bn_r, bn_two, ctx);
    }
    
    
    //printf("n = %s\n", number);
    printf("    n-1 = %s\n", BN_bn2dec(bn_n_minus_one));
    printf("    s = %s\n", BN_bn2dec(bn_s));
    printf("    r = %s\n", BN_bn2dec(bn_r));
    
    int s = atoi(BN_bn2dec(bn_s));
    BIGNUM * bn_a = BN_new();
    BIGNUM * bn_y = BN_new();
    int i = 0;
    int j = 0;
    unsigned char maxval[4];
    unsigned char factor[4];
    fseek(primesfile, 0 ,SEEK_SET);
    fread(maxval, 1, 4, primesfile);
    
    for (i=1; i<=atoi(maxitr); i++)
    {
        printf("    Itr %d of %d, ", i, atoi(maxitr));
        fread(factor, 1, 4, primesfile);
        BN_bin2bn(factor, 4, bn_a);
        
        
        if(BN_cmp(bn_a, bn_n_minus_one) == 1)
        {
            return -1;
        }
        
        
        BN_mod_exp(bn_y, bn_a, bn_r, bn_num, ctx);
        printf("a = %s, y = %s", BN_bn2dec(bn_a), BN_bn2dec(bn_y));
        
        if(BN_cmp(bn_y, bn_n_minus_one) == 0)
        {
            printf(" (which is n-1)");
        }
        printf("\n");
        
        
        if(BN_cmp(bn_y, bn_one) != 0 && BN_cmp(bn_y, bn_n_minus_one) != 0)
        {
            
            for(j=1; (j<=(s-1)) && BN_cmp(bn_y, bn_n_minus_one)!=0; j++)
            {
                BN_mod_sqr(bn_y, bn_y, bn_num, ctx);
                printf("      j = %d of %d, y = %s", j, s-1, BN_bn2dec(bn_y));
                
                if (BN_cmp(bn_y, bn_n_minus_one) == 0)
                {
                    printf(" (which is n-1)");
                }
                printf("\n");
                
                if(BN_cmp(bn_y, bn_one) == 0)
                {
                    printf("  Miller-Rabin found a strong witness %s\n", BN_bn2dec(bn_a));
                    return 1;
                }
            }
            
            if(BN_cmp(bn_y, bn_n_minus_one) != 0)
            {
                printf("  Miller-Rabin found a strong witness %s\n", BN_bn2dec(bn_a));
                return 1;
            }
            
        }
        
    }
    printf("  Miller-Rabin declares n to be a prime number\n");
    
    //printf("number is %s\n", number);
    //printf("maxitr is %s\n", maxitr);
    //printf("this is function millerrabin\n");
    return 0;
}


int RndOddNum(BIGNUM *bn_num, int numbits, int buffer_num, FILE *rndfile)
{
    int i = 0;
    unsigned char * buffer = (unsigned char *)calloc(buffer_num, sizeof(char));
    fread(buffer, 1, buffer_num, rndfile);
    
    
    
    BN_bin2bn(buffer, buffer_num, bn_num);
    BN_set_bit(bn_num, 0);
    BN_set_bit(bn_num, numbits - 1);
    
    for (i=numbits; i<buffer_num*8; i++)
    {
        BN_clear_bit(bn_num, i);
    }
    free(buffer);
    
    
    return 0;
}



int rndsearch(const char * numbits, const char * maxitr, FILE * primesfile, FILE * rndfile)
{
    int buffer_num = 0;
    int i = 0;
    BIGNUM * bn_num = BN_new();
    const char * number = NULL;
    
    if (atoi(numbits)%8 == 0)
    {
        buffer_num = atoi(numbits)/8;
    }
    else if (atoi(numbits)%8 != 0)
    {
        buffer_num = atoi(numbits)/8 + 1;
    }
    
    while(1)
    {
        i++;
        printf("RANDOM-SEARCH: iteration %d\n", i);
        
        BN_init(bn_num);
        RndOddNum(bn_num, atoi(numbits), buffer_num, rndfile);
        
        number = BN_bn2dec(bn_num);
        printf("  n = %s\n", number);
        
        if (trialdiv_rnd(number, primesfile) == 0)
        {
            if(millerrabin_rnd(number, maxitr, primesfile) == 0)
            {
                break;
            }
        }
        
    }
    
    
    //printf("numbits is %s\n", numbits);
    //printf("maxitr is %s\n", maxitr);
    //printf("this is function rndsearch\n");
    return 0;
}
