#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    int amount = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;
    char buff1[49] = "";
    char buff2[65] = "";
    char temp[5] = "";
    char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        printf("Open Error!\n");
        exit(1);
    }

    while (!feof(fp))
    {
        amount = 0;
        count = 0;
        
        for (i=0; i<65; i++)
        {
            buff2[i] = 0;
        }
        
        for (i=0; i<49; i++)
        {
            buff1[i] = 0;
        }
        
        
        
        for (i=0; i<64; i++)
        {
            buff2[i] = fgetc(fp);
            amount++;
            if (buff2[i] == EOF)
            {
                buff2[i] = 0;
                break;
            }
            else if (buff2[i] == '\n' || buff2[i] == '\r')
            {
                buff2[i] = 0;
                i--;
                amount--;
            }
            else if (buff2[i] == '=')
            {
                buff2[i] = 0;
                amount--;
                break;
            }
        }
        
        //printf("%s\n", buff2);
        //printf("%d\n", amount);
        
        for ( i = 0; base64[i] != '\0' ; i += 4 )
        {
            memset( temp, 0xFF, sizeof(temp) );
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64[k] == buff2[i] )
                    temp[0]= k;
            }
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64[k] == buff2[i+1] )
                    temp[1]= k;
            }
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64[k] == buff2[i+2] )
                    temp[2]= k;
            }
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64[k] == buff2[i+3] )
                    temp[3]= k;
            }
            
            buff1[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
            ((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
            if ( base64[i+2] == '=' )
                break;
            
            buff1[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
            ((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
            if ( base64[i+3] == '=' )
                break;
            
            buff1[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
            ((unsigned char)(temp[3]&0x3F));
        }
    
        fputs(buff1, stdout);
    }
        return 0;
}