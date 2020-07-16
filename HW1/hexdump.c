//
//  hexdump.c
//  
//
//  Created by Hongquan Kang (Simon) on 1/26/16.
//
//

#include <stdio.h>
#include <stdlib.h>

int hexdump(FILE *fp)
{
    //printf("This is function hexdump!\n");
    
    int count = 0;
    int i = 0;
    int buff = 0;
    char buff1[17] = "";
    buff1[16] = 0;
    
    //read the file
    buff = fgetc(fp);
    while(buff != EOF)
    {
        if(count % 16 == 0)
            printf("%06x: ", count);
        printf("%02x ", buff);
        if(buff>=32 && buff<=126)
            buff1[count % 16] = buff;
        else if(buff<=31 || buff == 127)
            buff1[count % 16] = 46;
        else if(buff>=128)
            buff1[count % 16] = 126;
        count++;
        if(count % 8 == 0)
            printf(" ");
        if(count % 16 == 0)
        {
            printf("%s\n", buff1);
            
        }
        buff = fgetc(fp);
    }
    
    for(i=0; i<(16-count%16); i++)
    {
        printf("-- ");
        if ((16-(count%16)-i-1)==8)
        {
            printf(" ");
        }
    }
    printf(" ");
    buff1[count%16] = 0;
    printf("%s", buff1);
    for(i=0; i<(16-count%16); i++)
    {
        printf(" ");
    }
    printf("\n");
    
    return 0;
}
