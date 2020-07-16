//
//  main.c
//  HW3
//
//  Created by Hongquan Kang on 2/23/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int keygen(const char * pphrase, int period);
int hw3_encrypt(FILE *fp, const char * key_file);
int invken(FILE *fp);
int histo(int period, int which_index, FILE * fp);
int solve(int len, FILE * fp);


int main(int argc, const char * argv[])
{
    const char * pphrase = NULL;
    const char * key_file;
    FILE *fp;
    int period = 0;
    int which_index = 0;
    int i = 0;
    int len = 0;
    
    
    if (argc > 1)
    {
        if (strcmp(argv[1], "keygen") == 0)
        {
            if (argc == 4)
            {
                for (i=2; i<4; i++)
                {
                    if (strncmp(argv[i], "-p=", 3) == 0)
                    {
                        pphrase = argv[i]+3;
                    }
                    if (strncmp(argv[i], "-t=", 3) == 0) {
                        period = atoi(argv[i]+3);
                    }
                }
                
                if (pphrase == NULL || period < 1)
                {
                    fprintf(stderr, "Command Error\n");
                    exit(1);
                }
                
                keygen(pphrase, period);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
        }
        
        
        else if (strcmp(argv[1], "crypt") == 0)
        {
            if (argc<3)
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            if (strncmp(argv[2], "-k=", 3) == 0)
            {
                key_file = argv[2]+3;
                if (argc == 4)
                {
                    fp = fopen(argv[3], "rb");
                    if (fp == NULL) {
                        fprintf(stderr, "File does not exist\n");
                        exit(1);
                    }
                }
                else if (argc == 3)
                {
                    fp = stdin;
                    fseek(fp, 0, SEEK_END);
                    if (ftell(fp) == 0)
                    {
                        fprintf(stderr, "Command Error or file does not exist\n");
                        exit(1);
                    }
                    fseek(fp, 0, SEEK_SET);
                }
                else
                {
                    fprintf(stderr, "Command Error\n");
                    exit(1);
                }
                hw3_encrypt(fp, key_file);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            
        }
        
        
        else if (strcmp(argv[1], "invkey") == 0)
        {
            if(argc == 3)
            {
                fp = fopen(argv[2], "rb");
                if(fp == NULL)
                {
                    fprintf(stderr, "the key file does not exist\n");
                    exit(1);
                }
                invken(fp);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
        }
        
        
        else if (strcmp(argv[1], "histo") == 0)
        {
            if(argc > 3)
            {
                for (i=2; i<4; i++)
                {
                    if (strncmp(argv[i], "-t=", 3) == 0)
                    {
                        period = atoi(argv[i]+3);
                    }
                    if (strncmp(argv[i], "-i=", 3) == 0)
                    {
                        which_index = atoi(argv[i]+3);
                    }
                }
            }
            else if (argc<4)
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            if (period<1 || which_index<1)
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            if (argc == 5)
            {
                
                
                fp = fopen(argv[4], "rb");
                if (fp == NULL)
                {
                    fprintf(stderr, "the file for histo does not exist\n");
                    exit(1);
                }
                histo(period, which_index, fp);
            }
            else if(argc == 4)
            {
                fp = stdin;
                histo(period, which_index, fp);
            }
            
            
        }
        
        
        else if (strcmp(argv[1], "solve") == 0)
        {
            if (argc == 4)
            {
                if (strncmp(argv[2], "-l=", 3) == 0)
                {
                    len = atoi(argv[2]+3);
                }
                
                if (len <= 0)
                {
                    fprintf(stderr, "Command Error\n");
                    exit(1);
                }
                
                fp = fopen(argv[3], "rb");
                if (fp == NULL)
                {
                    fprintf(stderr, "the file for solve does not exist\n");
                    exit(1);
                }
                
                solve(len, fp);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
            }
        }
        
        else
        {
            printf("Command input error!\n");
            exit(1);
        }
        
    }
    else
    {
        printf("Command input error!\n");
        exit(1);
    }
    
    //printf("Hello, World!\n");
    return 0;
}
