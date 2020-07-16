//
//  dec_base64.c
//  
//
//  Created by Hongquan Kang (Simon) on 1/26/16.
//
//

#include <stdio.h>
#include <stdlib.h>

int dec_base64(FILE *fp)
{
    //printf("This is function dec_base64!\n");
    
    int amount = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int temp = 0;
    int count = 0;
    char buff1[49] = "";
    char buff2[65] = "";
    char buff3[5] = "";
    int flag = 0;
    char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    while (!feof(fp))
    {
        amount = 0;
        count = 0;
        
        //reset the buff1 and buff2
        for (i=0; i<65; i++)
        {
            buff2[i] = 0;
        }
        
        for (i=0; i<49; i++)
        {
            buff1[i] = 0;
        }
        
        
        //read data from the file to buff2
        for (i=0; i<64; i++)
        {
            temp = fgetc(fp);
            if (temp == EOF)
            {
                break;
            }
            else if (temp == '\n' || temp == '\r')
            {
                i--;
            }
            else if (buff2[i] == '=')
            {
                break;
            }
            else
            {
                buff2[i] = temp;
                amount++;
            }
        }
        
        //printf("%s\n", buff2);
        //printf("%d\n", amount);
        
        //decoding
        for (i=0; i<amount; i+=4)
        {
            flag = 0;
            
            //reset buff3
            for (j=0; j<5; j++)
            {
                buff3[j] = 0;
            }
            
            //find each char based on the base64 table
            if(buff2[i] != 0)
            {
                for (j=0; j<64; j++)
                {
                    if (base64[j] == buff2[i])
                    {
                        buff3[0] = j;
                        flag = 1;
                    }
                }
            }
            if(buff2[i+1] != 0)
            {
                for (j=0; j<64; j++)
                {
                    if (base64[j] == buff2[i+1])
                    {
                        buff3[1] = j;
                        flag = 2;
                    }
                }
            }
            if(buff2[i+2] != 0)
            {
                for (j=0; j<64; j++)
                {
                    if (base64[j] == buff2[i+2])
                    {
                        buff3[2] = j;
                        flag = 3;
                    }
                }
            }
            if(buff2[i+3] != 0)
            {
                for (j=0; j<64; j++)
                {
                    if (base64[j] == buff2[i+3])
                    {
                        buff3[3] = j;
                        flag = 4;
                    }
                }
            }
            
            
            //calculating the ascii
            if (flag == 1) {
                printf("Input Data Error!\n");
                exit(1);
            }
            if (flag == 4) {
                buff1[count++] = ((buff3[0]<<2) & 0xfc) | ((buff3[1]>>4) & 0x03);
                buff1[count++] = ((buff3[1]<<4) & 0xf0) | ((buff3[2]>>2) & 0x0f);
                buff1[count++] = ((buff3[2]<<6) & 0xc0) | (buff3[3] & 0x3f);
                buff1[count] = 0;
            }
            if (flag == 3) {
                buff1[count++] = ((buff3[0]<<2) & 0xfc) | ((buff3[1]>>4) & 0x03);
                buff1[count++] = ((buff3[1]<<4) & 0xf0) | ((buff3[2]>>2) & 0x0f);
                buff1[count] = 0;
            }
            if (flag == 2) {
                buff1[count++] = ((buff3[0]<<2) & 0xfc) | ((buff3[1]>>4) & 0x03);
                buff1[count] = 0;
            }
            
        }
        
        //output the result
        for (k=0; k<count; k++) {
            fputc(buff1[k], stdout);
        }
        
    }

    return 0;
}
