//
//  hw1.c
//  
//
//  Created by Hongquan Kang (Simon) on 1/26/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hexdump(FILE *fp);
int enc_base64(FILE *fp);
int dec_base64(FILE *fp);

int main (int argc, char *argv[])
{
    int flag=0;
    
    FILE *fp = NULL;
    
    //input check
    
    if (argc == 1)
    {
        printf("Malformed command! The command format is './hw1 [hexdump/enc-base64/dec-base64] [file]'\n");
        exit(1);
    }
    else if(strcmp(argv[1], "hexdump")!=0 && strcmp(argv[1], "enc-base64")!=0 && strcmp(argv[1], "dec-base64")!=0 )
    {
        printf("Malformed command! The command format is './hw1 [hexdump/enc-base64/dec-base64] [file]'\n");
        exit(1);
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "hexdump") == 0)
        {
            flag = 1;
        }
        else if (strcmp(argv[1], "enc-base64") == 0)
        {
            flag = 2;
        }
        else if (strcmp(argv[1], "dec-base64") == 0)
        {
            flag = 3;
        }
        
        //need check the input
        
        switch (flag)
        {
            case 1:
                hexdump(stdin);
                break;
                
            case 2:
                enc_base64(stdin);
                break;
                
            case 3:
                dec_base64(stdin);
                break;
                
            default:
                break;
        }
        exit(0);
    }
    else if (argc != 3)
    {
        
        printf("Malformed command! The command format is './hw1 [hexdump/enc-base64/dec-base64] [file]'\n");
        exit(1);
    }
    
    
    
    //Open a file
    fp = fopen(argv[2], "rb");
    if (fp == NULL)
    {
        printf("Input file does not exist!\n");
        exit(1);
    }
    
    //Option Check
    if (strcmp(argv[1], "hexdump") == 0)
    {
        flag = 1;
    }
    else if (strcmp(argv[1], "enc-base64") == 0)
    {
        flag = 2;
    }
    else if (strcmp(argv[1], "dec-base64") == 0)
    {
        flag = 3;
    }
    
    switch (flag)
    {
        case 1:
            hexdump(fp);
            break;
            
        case 2:
            enc_base64(fp);
            break;
            
        case 3:
            dec_base64(fp);
            break;
            
        default:
            break;
    }
    
    fclose(fp);
    
    return 0;
}
