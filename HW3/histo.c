//
//  histo.c
//  HW3
//
//  Created by Simon Kang on 2/23/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int histo(int period, int which_index, FILE * fp)
{
    int count = 0;
    
    if (which_index > period || period < 1 || which_index < 1)
    {
        fprintf(stderr, "Command Error\n");
        exit(1);
    }
    
    char input_buffer[period];
    int check = 0;
    int alphabet_count[26];
    int alphabet_index[26];
    int i,j = 0;
    int temp = 0;
    
    for (i=0; i<26; i++)
    {
        alphabet_count[i] = 0;
        alphabet_index[i] = i;
    }
    
    while (fread(input_buffer, 1, period, fp))
    {
        check = input_buffer[which_index-1];
        
        if (check < 97 || check > 122)
        {
            continue;
        }
        else if (check >= 97 && check <= 122)
        {
            alphabet_count[check-97]++;
            count++;
        }
    }
    
    fprintf(stdout, "L=%d\n", count);
    
    for (i=0; i<26; i++)
    {
        for (j=i+1; j<26; j++)
        {
            if (alphabet_count[i] < alphabet_count[j])
            {
                temp = alphabet_count[i];
                alphabet_count[i] = alphabet_count[j];
                alphabet_count[j] = temp;
                temp = alphabet_index[i];
                alphabet_index[i] = alphabet_index[j];
                alphabet_index[j] = temp;
            }
            else if (alphabet_count[i] == alphabet_count[j])
            {
                if (alphabet_index[i] > alphabet_index[j])
                {
                    temp = alphabet_count[i];
                    alphabet_count[i] = alphabet_count[j];
                    alphabet_count[j] = temp;
                    temp = alphabet_index[i];
                    alphabet_index[i] = alphabet_index[j];
                    alphabet_index[j] = temp;
                }
            }
        }
    }
    
    for (i=0; i<26; i++)
    {
        printf("%c: %d (%.2f%%)\n", 97+alphabet_index[i], alphabet_count[i], ((double)(alphabet_count[i]*100) / count));
    }
    
    
    
    //printf("this is function histo\n");
    fclose(fp);
    return 0;
}

