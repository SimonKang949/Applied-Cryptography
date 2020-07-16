//
//  main.c
//  HW7
//
//  Created by Simon Kang on 4/25/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rc4(const char * pphrase, int len);
int x1(FILE * input_file);
int x2(FILE * input_file);
int x3(FILE * input_file);
int x4(FILE * input_file);
int x5(FILE * input_file, int dval);


int main(int argc, const char * argv[])
{
    FILE * input_file = NULL;
    const char * pphrase = NULL;
    int len = 0;
    int dval = 0;
    
    if (argc < 2)
    {
        fprintf(stderr, "Command Error\n");
        exit(1);
    }
    else
    {
        if (strncmp(argv[1], "rc4", 3) == 0)
        {
            if (argc == 3)
            {
                pphrase = argv[2]+3;
                len = 0;
                if (pphrase != NULL)
                {
                    rc4(pphrase, 0);
                }
            }
            else if (argc == 4)
            {
                if (strncmp(argv[2], "-p=", 3) == 0)
                {
                    if (strncmp(argv[3], "-l=", 3) == 0)
                    {
                        pphrase = argv[2]+3;
                        len = atoi(argv[3]+3);
                        if (pphrase != NULL && len != 0)
                        {
                            rc4(pphrase, len);
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Command Error\n");
                        exit(1);
                    }
                }
                else
                {
                    fprintf(stderr, "Command Error\n");
                    exit(1);
                }
                
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "x1", 2) == 0)
        {
            if (argc == 3)
            {
                input_file = fopen(argv[2], "rb");
                if (input_file == NULL)
                {
                    fprintf(stderr, "the input file does not exist\n");
                    exit(1);
                }
                x1(input_file);
                fclose(input_file);
            }
            else if (argc == 2)
            {
                x1(stdin);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "x2", 2) == 0)
        {
            if (argc == 3)
            {
                input_file = fopen(argv[2], "rb");
                if (input_file == NULL)
                {
                    fprintf(stderr, "the input file does not exist\n");
                    exit(1);
                }
                x2(input_file);
                fclose(input_file);
            }
            else if (argc == 2)
            {
                x2(stdin);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "x3", 2) == 0)
        {
            if (argc == 3)
            {
                input_file = fopen(argv[2], "rb");
                if (input_file == NULL)
                {
                    fprintf(stderr, "the input file does not exist\n");
                    exit(1);
                }
                x3(input_file);
                fclose(input_file);
            }
            else if (argc == 2)
            {
                x3(stdin);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "x4", 2) == 0)
        {
            if (argc == 3)
            {
                input_file = fopen(argv[2], "rb");
                if (input_file == NULL)
                {
                    fprintf(stderr, "the input file does not exist\n");
                    exit(1);
                }
                x4(input_file);
                fclose(input_file);
            }
            else if (argc == 2)
            {
                x4(stdin);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "x5", 2) == 0)
        {
            if (argc == 4)
            {
                if (strncmp(argv[2], "-d=", 2) == 0)
                {
                    dval = atoi(argv[2]+3);
                }
                else
                {
                    fprintf(stderr, "Command Error\n");
                    exit(1);
                }
                
                input_file = fopen(argv[3], "rb");
                if (input_file == NULL)
                {
                    fprintf(stderr, "the input file does not exist\n");
                    exit(1);
                }
                x5(input_file, dval);
                fclose(input_file);
            }
            else if (argc == 3)
            {
                if (strncmp(argv[2], "-d=", 2) == 0)
                {
                    dval = atoi(argv[2]+3);
                }
                else
                {
                    fprintf(stderr, "the input file does not exist\n");
                    exit(1);
                }
                
                x5(stdin,dval);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
        }
        
        else
        {
            fprintf(stderr, "Command Error\n");
            exit(1);
        }
    }
    
    // insert code here...
    //printf("Hello, World!\n");
    return 0;
}
