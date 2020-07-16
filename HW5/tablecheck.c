//
//  tablecheck.c
//  HW5
//
//  Created by Simon Kang on 4/1/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_hex(char check)
{
    if (check >= '0' && check <= '9')
    {
        return 0;
    }
    else if (check >= 'a' && check <= 'f')
    {
        return 0;
    }
    else if (check >= 'A' && check <= 'F')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int check_s(FILE * tablefile)
{
    const char * header = "S=";
    char * s_buffer = (char *)calloc(1, 640);
    int val_count[256] = {0};
    unsigned int i = 0;
    char temp_values[3] = {0};
    int temp_index = 0;
    
    fseek(tablefile, 0, SEEK_SET);
    while (strncmp(s_buffer, header, strlen(header)) != 0)
    {
        if (!fgets(s_buffer, 640, tablefile ))
        {
            fprintf(stderr, "S line does not be found\n");
            exit(1);
        }
    }
    
    for (i = (unsigned int)strlen(header); i<strlen(s_buffer)-1; i+=2)
    {
        if (check_hex(s_buffer[i]) || check_hex(s_buffer[i+1]))
        {
            fprintf(stderr, "S in tablefile does not correct\n");
            exit(1);
        }
        
        temp_values[0] = s_buffer[i];
        temp_values[1] = s_buffer[i+1];
        temp_values[2] = ' ';
        temp_index = (int) strtol(temp_values, NULL, 16);
        val_count[temp_index] += 1;
    }
    
    for(i=0; i<256; i++)
    {
        if(val_count[i] != 1)
        {
            char val[3];
            sprintf(val, "%02x", i);
            if(val_count[i] < 1)
            {
                fprintf(stderr,"value '%s' did not be found in the tablefile.\n", val);
                exit(1);
            }
            else if(val_count[i] > 1)
            {
                fprintf(stderr, "value '%s' did not be found more than once in the tablefile.\n", val);
                exit(1);
            }
        }
    }
    
    
    //printf("S correct\n");
    return 0;
}

int check_p(FILE * tablefile)
{
    const char * header = "P=";
    char * p_buffer = (char *)calloc(1, 16);
    char temp_values[3] = {0};
    int i = 0;
    
    fseek(tablefile, 0, SEEK_SET);
    while (strncmp(p_buffer, header, strlen(header)) != 0)
    {
        if (!fgets(p_buffer, 16, tablefile ))
        {
            fprintf(stderr, "P line does not be found\n");
            exit(1);
        }
        p_buffer[strlen(p_buffer)-1] = '\0';
    }
    
    if (strlen(p_buffer) != (strlen(header)+8))
    {
        fprintf(stderr, "P does not 8 characters\n");
        exit(1);
    }
    
    for (i=0; i<4; i++)
    {
        temp_values[0] = *(p_buffer+strlen(header) + i*2);
        temp_values[1] = *(p_buffer+strlen(header) + i*2+1);
        temp_values[2] = ' ';
        
        if (check_hex(temp_values[0]) || check_hex(temp_values[1]))
        {
            fprintf(stderr, "S in tablefile does not correct\n");
            exit(1);
        }
        
    }
    
    //printf("P correct\n");
    return 0;
}

int check_invp(FILE * tablefile)
{
    const char * header = "INVP=";
    char * invp_buffer = (char *)calloc(1, 16);
    char temp_values[3] = {0};
    int i = 0;
    
    fseek(tablefile, 0, SEEK_SET);
    while (strncmp(invp_buffer, header, strlen(header)) != 0)
    {
        if (!fgets(invp_buffer, 16, tablefile ))
        {
            fprintf(stderr, "P line does not be found\n");
            exit(1);
        }
        invp_buffer[strlen(invp_buffer)-1] = '\0';
    }
    
    if (strlen(invp_buffer) != (strlen(header)+8))
    {
        fprintf(stderr, "P does not 8 characters\n");
        exit(1);
    }
    
    for (i=0; i<4; i++)
    {
        temp_values[0] = *(invp_buffer+strlen(header) + i*2);
        temp_values[1] = *(invp_buffer+strlen(header) + i*2+1);
        temp_values[2] = ' ';
        
        if (check_hex(temp_values[0]) || check_hex(temp_values[1]))
        {
            fprintf(stderr, "S in tablefile does not correct\n");
            exit(1);
        }
        
    }
    
    //printf("INVP correct\n");
    return 0;
}




int tablecheck(FILE * tablefile)
{
    if (check_s(tablefile))
    {
        fprintf(stderr, "S in tablefile does not correct\n");
        exit(1);
    }
    
    if (check_p(tablefile))
    {
        fprintf(stderr, "P in tablefile does not correct\n");
        exit(1);
    }
    
    if (check_invp(tablefile))
    {
        fprintf(stderr, "INVP in tablefile does not correct\n");
        exit(1);
    }
    
    //printf("this is function tablecheck\n");
    return 0;
}
