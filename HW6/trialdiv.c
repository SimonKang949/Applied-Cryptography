//
//  trialdiv.c
//  HW6
//
//  Created by Simon Kang on 4/12/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <arpa/inet.h>

int trialdiv(const char * number, FILE * primesfile)
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
            printf("n is composite by trial division (mod %s = 0)\n", BN_bn2dec(bn_factor));
            return 1;
        }
    }
    
    BN_sqr(bn_square, bn_maxval, ctx);
    
    if(BN_cmp(bn_square, bn_num) == 0)
    {
        printf("n passes trial division test (not enough primes)\n");
    }
    else
    {
        printf("n passes trial division test\n");
    }
    
    //printf("the number is %d\n", number);
    //printf("this is function trialdiv\n");
    return 0;
}
