//
//  main.c
//  HW4
//
//  Created by Simon Kang on 3/10/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tablecheck(FILE *fp);
int DES_encrypt(FILE *fp, FILE *fp_input, const char * key);
int DES_decrypt(FILE *fp, FILE *fp_input, const char * key);
int encrypt3(FILE *fp, FILE *fp_input, const char * key);
int decrypt3(FILE *fp, FILE *fp_input, const char * key);

int main(int argc, const char * argv[])
{
    FILE *fp = NULL;
    FILE *fp_input = NULL;
    int i = 0;
    const char * key = NULL;
    const char * table_file = NULL;
    
    if(argc>=3)
    {
        if (strncmp(argv[1], "tablecheck", 10) == 0)
        {
            if (argc == 3)
            {
                if (strncmp(argv[2], "-t=", 3) == 0)
                {
                    fp = fopen(argv[2]+3, "rb");
                    if (fp == NULL)
                    {
                        fprintf(stderr, "tablefile does not exist\n");
                        exit(1);
                    }
                    tablecheck(fp);
                }
                else
                {
                    fprintf(stderr, "Input command error\n");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr, "Input command error\n");
                exit(1);
            }
        }
        
        else if (strncmp(argv[1], "encrypt", 7) == 0)
        {
            if (argc >= 4)
            {
                for (i=2; i<=3; i++)
                {
                    if (strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if (strncmp(argv[i], "-t=", 3) == 0)
                    {
                        table_file = argv[i]+3;
                    }
                }
                
                if (argc == 5)
                {
                    fp_input = fopen(argv[4], "rb");
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "input file does not exist\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            DES_encrypt(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else if (argc == 4)
                {
                    fp_input = stdin;
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "no input data\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            DES_encrypt(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else
                {
                    fprintf(stderr, "command error 5\n");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr, "command error\n");
                exit(1);
            }
        }
        else if (strncmp(argv[1], "decrypt", 7) == 0)
        {
            if (argc >= 4)
            {
                for (i=2; i<=3; i++)
                {
                    if (strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if (strncmp(argv[i], "-t=", 3) == 0)
                    {
                        table_file = argv[i]+3;
                    }
                }
                
                if (argc == 5)
                {
                    fp_input = fopen(argv[4], "rb");
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "input file does not exist\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            DES_decrypt(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else if (argc == 4)
                {
                    fp_input = stdin;
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "no input data\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            DES_decrypt(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else
                {
                    fprintf(stderr, "command error 5\n");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr, "command error\n");
                exit(1);
            }
        }
        else if (strncmp(argv[1], "encrypt3", 8) == 0)
        {
            if (argc >= 4)
            {
                for (i=2; i<=3; i++)
                {
                    if (strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if (strncmp(argv[i], "-t=", 3) == 0)
                    {
                        table_file = argv[i]+3;
                    }
                }
                
                if (argc == 5)
                {
                    fp_input = fopen(argv[4], "rb");
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "input file does not exist\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            encrypt3(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else if (argc == 4)
                {
                    fp_input = stdin;
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "no input data\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            encrypt3(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else
                {
                    fprintf(stderr, "command error 5\n");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr, "command error\n");
                exit(1);
            }
        }
        else if (strncmp(argv[1], "decrypt3", 8) == 0)
        {
            if (argc >= 4)
            {
                for (i=2; i<=3; i++)
                {
                    if (strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if (strncmp(argv[i], "-t=", 3) == 0)
                    {
                        table_file = argv[i]+3;
                    }
                }
                
                if (argc == 5)
                {
                    fp_input = fopen(argv[4], "rb");
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "input file does not exist\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            decrypt3(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else if (argc == 4)
                {
                    fp_input = stdin;
                    if (fp_input == NULL)
                    {
                        fprintf(stderr, "no input data\n");
                        exit(1);
                    }
                    else
                    {
                        fp = fopen(table_file, "rb");
                        if (fp == NULL)
                        {
                            fprintf(stderr, "input table file does not exist\n");
                        }
                        else
                        {
                            decrypt3(fp, fp_input, key);
                            fclose(fp_input);
                        }
                    }
                }
                else
                {
                    fprintf(stderr, "command error 5\n");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr, "command error\n");
                exit(1);
            }
        }
    }
    else
    {
        fprintf(stderr, "Input command error\n");
        exit(1);
    }
    
    fclose(fp);
    return 0;
}
