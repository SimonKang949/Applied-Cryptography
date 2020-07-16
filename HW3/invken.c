//
//  invken.c
//  HW3
//
//  Created by Simon Kang on 2/23/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int invken(FILE *fp)
{
    int amount = 0;
    int count = 0;
    int input = 0;
    int i,j = 0;
    
    char state[26] = "abcdefghijklmnopqrstuvwxyz";
    
    fseek(fp, 0, SEEK_END);
    amount = (int)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    if (amount%27 != 0)
    {
        fprintf(stderr, "Input key file format error\n");
        exit(1);
    }
    
    char key_buff[27] = "";
    
    count = 0;
    
    input = fgetc(fp);
    
    while (input != EOF)
    {
        key_buff[count++] = input;
        if (count == 27)
        {
            for(i=0; i<26; i++)
            {
                for (j=0; j<26; j++)
                {
                    if (key_buff[j] == (97+i))
                    {
                        printf("%c", state[j]);
                    }
                }
            }
            printf("\n");
            count = 0;
        }
        
        input = fgetc(fp);
    }
    
    fclose(fp);
    
    //printf("this is function invken\n");
    return 0;
}

