//
//  maurer.c
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

int trialdiv_maurer(const char * number, FILE * primesfile)
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
            printf("    n is composite by trial division (mod %s = 0)\n", BN_bn2dec(bn_factor));
            return 1;
        }
    }
    
    BN_sqr(bn_square, bn_maxval, ctx);
    
    if(BN_cmp(bn_square, bn_num) == 0)
    {
        printf("    n passes trial division test (not enough primes)\n");
    }
    else
    {
        printf("    n passes trial division test\n");
    }
    
    //printf("the number is %d\n", number);
    //printf("this is function trialdiv\n");
    return 0;
}

int RndOddNum(BIGNUM *bn_num, int numbits, int buffer_num, FILE *rndfile);

unsigned char RndByte(FILE* rndfile)
{
    unsigned char rnd_byte;
    fread(&rnd_byte, 1, 1, rndfile);
    return rnd_byte;
}

unsigned char * maurer(const char * numbits, FILE * primesfile, FILE * rndfile, BIGNUM * bn_num, int level)
{
    fprintf(stdout, "Maurer: level %d, k=%s\n", level, numbits);
    
    BN_init(bn_num);
    
    int num = atoi(numbits);
    int buffer_num = 0;
    int cal_k = 0;
    
    if (atoi(numbits)%8 == 0)
    {
        buffer_num = atoi(numbits)/8;
    }
    else if (atoi(numbits)%8 != 0)
    {
        buffer_num = atoi(numbits)/8 + 1;
    }
    
    
    if (num <= 20)
    {
        while(1)
        {
            RndOddNum(bn_num, num, buffer_num, rndfile);
            printf("  step 1.1, n = %s\n", BN_bn2dec(bn_num));
            
            if (trialdiv_maurer(BN_bn2dec(bn_num), primesfile) == 0)
            {
                break;
            }
        }
        if (level == 0)
        {
            printf("\nMaurer's Algorithm found an %s-bit prime:\n  n = %s\n", numbits, BN_bn2dec(bn_num));
        }
        return BN_bn2dec(bn_num);
    }
    
    int m = 20;
    double c = 0.1;
    double B = c * num * num;
    double r = 0.5;
    
    if(num <= 2*m)
    {
        r = 0.5;
        printf("  step 4, r = %d%%\n", round( r*100.0 ));
    }
    
    if (num > 2*m)
    {
        unsigned char rnd_byte;
        while (1)
        {
            rnd_byte = RndByte(rndfile);
            r = rnd_byte / 255.0;
            r = 0.5 + r / 2.0;
            
            if (num*(1-r) > m)
            {
                break;
            }
        }
        
        printf("  step 4, random byte = %d, r = %d%%\n", rnd_byte, round(r * 100.0));
    }
    
    
    unsigned char * q = NULL;
    char * temp = NULL;
    sprintf(temp, "%d", (int)(floor(r*num)+1));
    
    
    q = maurer(temp, primesfile, rndfile, bn_num,level+1);
    
    BIGNUM * bn_q = BN_new();
    BN_dec2bn(&bn_q, q);
    
    printf("Maurer: back to level %d, k=%d, q=%s\n", level, num, q);
    int num_bits_in_q = 0;
    int num_bits_in_n = 0;
    
    num_bits_in_q = BN_num_bits(bn_q);
    
    
    BIGNUM * bn_I = BN_new();
    BIGNUM * bn_k = BN_new();
    BIGNUM * bn_one = BN_new();
    BIGNUM * bn_two = BN_new();
    BIGNUM * bn_k_minus_two = BN_new();
    BN_CTX * ctx = BN_CTX_new();
    
    BN_dec2bn(&bn_k, numbits);
    BN_dec2bn(&bn_one, "1");
    BN_dec2bn(&bn_two, "2");
    BN_sub(bn_k_minus_two, bn_k, bn_two);
    
    BN_exp(bn_I, bn_two, bn_k_minus_two, ctx);
    BN_div(bn_I, NULL, bn_I, bn_q, ctx);
    
    BIGNUM * bn_R = BN_new();
    
    int count = 1;
    
    BIGNUM * bn_a = BN_new();
    BIGNUM * bn_b = BN_new();
    BIGNUM * bn_d = BN_new();
    BIGNUM * bn_n_minus_one = BN_new();
    BIGNUM * bn_temp = BN_new();
    
    
    
    while (1)
    {
        num = num+1-num_bits_in_q;
        if (num%8 == 0)
        {
            buffer_num = num/8;
        }
        else if (num%8 != 0)
        {
            buffer_num = num/8 + 1;
        }
        RndOddNum(bn_R, num, buffer_num, rndfile);
        
        BN_mod(bn_R, bn_R, bn_I, ctx);
        BN_add(bn_R, bn_R, bn_I);
        BN_add(bn_R, bn_R, bn_one);
        
        BN_mul(bn_num, bn_two, bn_R, ctx);
        BN_mul(bn_num, bn_num, bn_q, ctx);
        BN_add(bn_num, bn_num, bn_one);
        
        printf("  step 7, itr %d: R = %s, n = %s\n", count, BN_bn2dec(bn_R), BN_bn2dec(bn_num));
        
        if (trialdiv_maurer(BN_bn2dec(bn_num), primesfile) != 1)
        {
            num_bits_in_n = BN_num_bits(bn_num);
            BN_sub(bn_n_minus_one, bn_num, bn_one);
            
            num = num_bits_in_n;
            if (num%8 == 0)
            {
                buffer_num = num/8;
            }
            else if (num%8 != 0)
            {
                buffer_num = num/8 + 1;
            }
            
            do
            {
                
                RndOddNum(bn_a, num, buffer_num, rndfile);
            }while( BN_cmp(bn_a, bn_one)<= 0 || BN_cmp(bn_a, bn_n_minus_one)>=0 );
            
            printf("  step 7.2.1, itr %d: a = %s\n", count, BN_bn2dec(bn_a));
            
            BN_mod_exp(bn_b, bn_a, bn_n_minus_one, bn_num, ctx);
            
            if(BN_cmp(bn_b, bn_one) == 0)
            {
                BN_mul(bn_temp, bn_two, bn_R, ctx);
                BN_mod_exp(bn_b, bn_a, bn_temp, bn_num, ctx);
                
                BN_sub(bn_temp, bn_b, bn_one);
                BN_gcd(bn_d, bn_temp, bn_num, ctx);
                
                if(BN_is_one(bn_d))
                {
                    if(level==0)printf("\nMaurer's Algorithm found an %d-bit prime:\n  n = %s\n", num, BN_bn2dec(bn_num));
                    return BN_bn2dec(bn_num);
                }
                
            }
            
        }
        
        count++;
    }
    
    
    
    //printf("numbits is %s\n", numbits);
    //printf("this is function maurer\n");
    //return 0;
}
