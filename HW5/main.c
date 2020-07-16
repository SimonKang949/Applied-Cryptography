//
//  main.c
//  HW5
//
//  Created by Simon Kang on 4/1/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tablecheck(FILE * tablefile);
int modprod(const char * poly1, const char * poly2);
int keyexpand(const char * key, FILE* tablefile);
int aes_encrypt(const char * key, FILE * tablefile, FILE * input_file);
int aes_decrypt(const char * key, FILE * tablefile, FILE * input_file);
int inverse(const char * poly);

int main(int argc, const char * argv[])
{
    FILE * tablefile = NULL;
    FILE * input_file = NULL;
    int i = 0;
    const char * poly1 = NULL;
    const char * poly2 = NULL;
    const char * poly = NULL;
    const char * key = NULL;
    
    
    if (argc < 2)
    {
        fprintf(stderr, "Command Error < 2!\n");
        exit(1);
    }
    else
    {
        if (strcmp(argv[1], "tablecheck") == 0)
        {
            if (argc == 3)
            {
                if (strncmp(argv[2], "-t=", 3) == 0)
                {
                    tablefile = fopen(argv[2]+3, "rb");
                    //printf("%s\n", argv[2]+3);
                    if (tablefile == NULL)
                    {
                        fprintf(stderr, "tablefile does not exist\n");
                        exit(1);
                    }
                    else
                    {
                        tablecheck(tablefile);
                    }
                }
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            //printf("tablecheck\n");
        }
        else if (strcmp(argv[1], "modprod") == 0)
        {
            if (argc == 4)
            {
                for (i=2; i<4; i++)
                {
                    if(strncmp(argv[i], "-p1=", 4) == 0)
                    {
                        poly1 = argv[i]+4;
                    }
                    else if(strncmp(argv[i], "-p2=", 4) == 0)
                    {
                        poly2 = argv[i]+4;
                    }
                }
                
                modprod(poly1, poly2);
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            //printf("modprod\n");
        }
        else if (strcmp(argv[1], "keyexpand") == 0)
        {
            if (argc == 4)
            {
                for (i=2; i<4; i++)
                {
                    if(strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if(strncmp(argv[i], "-t=", 3) == 0)
                    {
                        tablefile = fopen(argv[i]+3, "rb");
                        if (tablefile == NULL)
                        {
                            fprintf(stderr, "tablefile does not exist\n");
                            exit(1);
                        }
                        else
                        {
                            keyexpand(key, tablefile);
                        }
                    }
                }
            }
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            
            //printf("keyexpand\n");
        }
        else if (strcmp(argv[1], "encrypt") == 0)
        {
            if (argc == 5)
            {
                for (i=2; i<4; i++)
                {
                    if(strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if(strncmp(argv[i], "-t=", 3) == 0)
                    {
                        tablefile = fopen(argv[i]+3, "rb");
                        if (tablefile == NULL)
                        {
                            fprintf(stderr, "tablefile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                input_file = fopen(argv[4], "rb");
                if(input_file == NULL)
                {
                    fprintf(stderr, "input file does not exist\n");
                    exit(1);
                }
                aes_encrypt(key, tablefile, input_file);
                fclose(input_file);
                
            }
            
            else if (argc == 4)
            {
                for (i=2; i<4; i++)
                {
                    if(strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if(strncmp(argv[i], "-t=", 3) == 0)
                    {
                        tablefile = fopen(argv[i]+3, "rb");
                        if (tablefile == NULL)
                        {
                            fprintf(stderr, "tablefile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                aes_encrypt(key, tablefile, stdin);
                
            }
            
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            //printf("encrypt\n");
        }
        else if (strcmp(argv[1], "decrypt") == 0)
        {
            if (argc == 5)
            {
                for (i=2; i<4; i++)
                {
                    if(strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if(strncmp(argv[i], "-t=", 3) == 0)
                    {
                        tablefile = fopen(argv[i]+3, "rb");
                        if (tablefile == NULL)
                        {
                            fprintf(stderr, "tablefile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                input_file = fopen(argv[4], "rb");
                if(input_file == NULL)
                {
                    fprintf(stderr, "input file does not exist\n");
                    exit(1);
                }
                aes_decrypt(key, tablefile, input_file);
                fclose(input_file);
                
            }
            
            else if (argc == 4)
            {
                for (i=2; i<4; i++)
                {
                    if(strncmp(argv[i], "-k=", 3) == 0)
                    {
                        key = argv[i]+3;
                    }
                    else if(strncmp(argv[i], "-t=", 3) == 0)
                    {
                        tablefile = fopen(argv[i]+3, "rb");
                        if (tablefile == NULL)
                        {
                            fprintf(stderr, "tablefile does not exist\n");
                            exit(1);
                        }
                    }
                }
                
                aes_decrypt(key, tablefile, stdin);
                
            }
            
            else
            {
                fprintf(stderr, "Command Error\n");
                exit(1);
            }
            
            //printf("decrypt\n");
        }
        else if (strcmp(argv[1], "inverse") == 0)
        {
            if (argc == 3)
            {
                if(strncmp(argv[2], "-p=", 3) == 0)
                {
                    poly = argv[2]+3;
                }
                
                inverse(poly);
                
            }
            else
            {
                fprintf(stderr, "Command Error! not match\n");
                exit(1);
            }
            
            
            //printf("inverse\n");
        }
        else
        {
            fprintf(stderr, "Command Error! not match\n");
            exit(1);
        }
    }
    
    
    fclose(tablefile);
    //printf("Hello, World!\n");
    return 0;
}
