//
//  enc_base64.c
//  
//
//  Created by Hongquan Kang (Simon) on 1/26/16.
//
//

#include <stdio.h>

int enc_base64(FILE *fp)
{
    //printf("This is function enc_base64!\n");
    
    int amount = 0;
    int i = 0;
    int count = 0;
    char buff1[49] = "";
    char buff2[65] = "";
    int flag = 0;
    buff1[48] = 0;
    buff2[64] = 0;
    char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    
    while (!feof(fp))
    {
        count = 0;
        
        //reset buff2
        for (i=0; i<64; i++)
        {
            buff2[i] = 0;
        }
        
        //read data into buff1 from the file
        amount = fread(buff1, 1, 48, fp);
        
        //encoding
        for (i=0; i<amount; i+=3)
        {
            flag = (buff1[i]>>2) & 0x3f;
            buff2[count++] = base64[flag];
            
            flag = (buff1[i]<<4) & 0x30;
            if (amount <= i+1)
            {
                buff2[count++] = base64[flag];
                buff2[count++] = '=';
                buff2[count++] = '=';
                break;
            }
            flag |= (buff1[i+1]>>4) & 0x0f;
            buff2[count++] = base64[flag];
            
            flag = (buff1[i+1]<<2) & 0x3c;
            if (amount <= i+2)
            {
                buff2[count++] = base64[flag];
                buff2[count++] = '=';
                break;
            }
            flag |= (buff1[i+2]>>6) & 0x03;
            buff2[count++] = base64[flag];
            
            flag = buff1[i+2] & 0x3f;
            buff2[count++] = base64[flag];
            
        }
        
        //output the result
        printf("%s\n", buff2);
        
    }

    
    return 0;
}
