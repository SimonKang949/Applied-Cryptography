//
//  crypt.c
//  HW3
//
//  Created by Simon Kang on 2/23/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int hw3_encrypt(FILE *fp, const char * key_file)
{
    FILE * fp_key = NULL;
    int amount =0;
    int row = 0;
    int count = 0;
    int i = 0;
    int input_file_buff = 0;
    //char state[26] = "abcdefghijklmnopqrstuvwxyz";
    
    
    
    
    fp_key = fopen(key_file, "rb");
    if (fp_key == NULL)
    {
        fprintf(stderr, "Key file does not exist\n");
    }
    
    fseek(fp_key, 0, SEEK_END);
    amount = (int)ftell(fp_key);
    
    if (amount%27 != 0)
    {
        fprintf(stderr, "Input key file format error\n");
        exit(1);
    }
    else if(amount%27 ==0)
    {
        row = amount/27;
    }
    
    char key_buff[row][27];
    fseek(fp_key, 0, SEEK_SET);
    
    while (!feof(fp_key))
    {
        fread(key_buff[count++], 1, 27, fp_key);
        if (count == row)
        {
            break;
        }
    }
    
    
    input_file_buff = fgetc(fp);
    i=0;
    while (input_file_buff != EOF)
    {
        if (input_file_buff == '\n')
        {
            break;
        }
        else if (input_file_buff>=97 && input_file_buff<=122)
        {
            count = input_file_buff - 97;
            
            fprintf(stdout, "%c", key_buff[i++][count]);
        }
        else
        {
            fprintf(stdout, "%c", input_file_buff);
            i++;
        }
        input_file_buff = getc(fp);
        
        if (i == row)
        {
            i=0;
        }
        
    }
    
    
    fprintf(stdout, "\n");
    fclose(fp_key);
    fclose(fp);
    
    
    //printf("this is function hw3_encrypt\n");
    return 0;
}

