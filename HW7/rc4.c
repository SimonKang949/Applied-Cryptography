//
//  rc4.c
//  HW7
//
//  Created by Simon Kang on 4/26/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

static unsigned char state[256], x, y;


int rc4(const char * pphrase, int len)
{
    
    int i = 0;
    unsigned char * key_buff = malloc(256 * sizeof(char));
    unsigned char * buffer_pointer = key_buff;
    unsigned char index = 0;
    
    char md5_buf[MD5_DIGEST_LENGTH];
    char *s=malloc(strlen(pphrase)+3);
    
    for (i=0; i < 16; i++)
    {
        sprintf(s, "%02d%s", i, pphrase);
        MD5(s, strlen(s), md5_buf);
        memcpy(buffer_pointer, md5_buf, sizeof(md5_buf));
        buffer_pointer += sizeof(md5_buf);
    }
    free(s);
    
    unsigned char t, j, k=0;
    for (i=0; i < 256; i++)
    {
        state[i] = i;
    }
    for (i=0, j=0; i < 256; i++, j=(j+1)%256)
    {
        t = state[i];
        state[i] = state[k+= key_buff[j] + t];
        state[k] = t;
    }
    x = y = 0;
    
    if (len == 0)
    {
        fwrite(state, 1, sizeof(state), stdout);
    }
    else
    {
        i=0;
        t=0;
        while (i<len)
        {
            x=(x+1)%256;
            y=(y+state[x])%256;
            t = state[y];
            state[y] = state[x];
            state[x] = t;
            index = (state[x] + state[y])%256;
            fputc(state[index], stdout);
            i++;
        }
    }
    
    //printf("\n");
    //printf("this is function rc4\n");
    //printf("the pphrase is %s\n", pphrase);
    //printf("the len of pphrase is %lu\n", strlen(pphrase));
    //printf("the len is %d\n", len);
    return 0;
}
