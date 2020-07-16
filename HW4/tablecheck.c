//
//  tablecheck.c
//  HW4
//
//  Created by Simon Kang on 3/10/16.
//  Copyright © 2016 Hongquan Kang (Simon). All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_line_format(FILE *fp, int * check_values, char * line_header, int len)
{
    char * line_buffer = (char *)calloc(1, 200);
    char * values = NULL;
    int i = 0;
    
    fseek(fp, 0, SEEK_SET);
    while (strncmp(line_buffer, line_header, strlen(line_header)) != 0)
    {
        if(!fgets(line_buffer, 200, fp))
        {
            fprintf(stderr, "the %s line is not found\n", line_header);
            return 1;
        }
    }
    
    values = line_buffer + strlen(line_header);
    for (i=0; i<len; i++)
    {
        if (values == NULL)
        {
            fprintf(stderr, "%s line values are insufficient\n", line_header);
            return 1;
        }
        
        
        check_values[i] = atoi(values);
        values = strchr(values+1, ',');
        if (values != NULL)
        {
            values = values+1;
        }
        
    }
    
    if (values != NULL) {
        fprintf(stderr, "%s line values are more than %d\n", line_header, len);
        return 1;
    }
    
    free(line_buffer);
    return 0;
}


int check_pc2(FILE *fp)
{
    char * line_header = (char *)"PC2=";
    int pc2_values[48];
    int values_frequency[56];
    
    int i = 0;
    
    for(i=0; i< 56; i++)
    {
        values_frequency[i] = 0;
    }
    
    if (check_line_format(fp, pc2_values, line_header, 48))
    {
        return 1;
    }
    
    /*
    for (i=0; i<48; i++)
    {
        printf("%2d ", pc2_values[i]);
    }
    printf("\n");
    */
    
    for (i=0; i<48; i++)
    {
        if (pc2_values[i]<1 || pc2_values[i]>56)
        {
            fprintf(stderr, "the values in line %s are not from 1 to 56\n", line_header);
            return 1;
        }
        else
        {
            values_frequency[pc2_values[i]-1]++;
        }
    }
    
    for (i=0; i<56; i++)
    {
        if (values_frequency[i] != 0)
        {
            if (values_frequency[i] != 1)
            {
                fprintf(stderr, "the values in line %s do not appears only 0 or 1 times\n", line_header);
                return 1;
            }
        }
    }
    
    
    return 0;
}


int check_pc1(FILE *fp)
{
    char * line_header = (char *)"PC1=";
    int pc1_values[56];
    int values_frequency[64];
    
    int i = 0;
    
    for(i=0; i< 64; i++)
    {
        values_frequency[i] = 0;
    }
    
    if (check_line_format(fp, pc1_values, line_header, 56))
    {
        return 1;
    }
    
    /*
    for (i=0; i<56; i++)
    {
        printf("%2d ", pc1_values[i]);
    }
    printf("\n");
    */
    
    for (i=0; i<56; i++)
    {
        if (pc1_values[i]<1 || pc1_values[i]>64)
        {
            fprintf(stderr, "the values in line %s are not from 1 to 64\n", line_header);
            return 1;
        }
        else
        {
            values_frequency[pc1_values[i]-1]++;
        }
    }
    
    for (i=0; i<64; i++)
    {
        if ((i+1)%8 != 0 && values_frequency[i] == 0)
        {
            fprintf(stderr, "some values in line %s appear more than once", line_header);
            return 1;
        }
        else if((i+1)%8 == 0 && values_frequency[i] != 0)
        {
            fprintf(stderr, "the values in line %s contains the multiples of 8\n", line_header);
            return 1;
        }
    }
    
    
    return 0;
}


int check_v(FILE *fp)
{
    char * line_header = (char *)"V=";
    int v_values[16];
    int values_frequency[2];
    
    int i = 0;
    
    for (i=0; i<2; i++)
    {
        values_frequency[i] = 0;
    }
    
    if (check_line_format(fp, v_values, line_header, 16))
    {
        return 1;
    }
    
    /*
    for (i=0; i<16; i++)
    {
        printf("%2d ", v_values[i]);
    }
    printf("\n");
    */
    
    for (i=0; i<16; i++)
    {
        if (v_values[i]!=1 && v_values[i]!=2)
        {
            fprintf(stderr, "the values in line %s are not 1 or 2\n", line_header);
            return 1;
        }
        else
        {
            values_frequency[v_values[i]-1]++;
        }
    }
    
    if (values_frequency[0] != 4)
    {
        if (values_frequency[1] != 12)
        {
            fprintf(stderr, "In %s line, the 1 does not appear 4 times, and 2 does not appear 12 times\n", line_header);
            return 1;
        }
    }
    
    return 0;
    
}



int check_s(FILE *fp)
{
    char * line_header = malloc(3);
    int s_values[64];
    int values_frequency[16];
    
    int i=0;
    int j=0;
    int k=0;
    
    for (i=1; i<=8; i++)
    {
        sprintf(line_header, "S%d=",i);
        //printf("%s\n", line_header);
        
        if (check_line_format(fp, s_values, line_header, 64))
        {
            return 1;
        }
        
        for (j=0; j<4; j++)
        {
            for (k=0; k<16; k++)
            {
                values_frequency[k] = 0;
            }
            
            for (k=0; k<16; k++)
            {
                if (s_values[j*16+k] < 0 || s_values[j*16+k] > 15)
                {
                    fprintf(stderr, "the values in line %s are not between 0 to 15\n", line_header);
                    return 1;
                }
                else
                {
                    values_frequency[s_values[j*16+k]]++;
                }
                
            }
            
            for (k=0; k<16; k++)
            {
                if (values_frequency[k] != 1)
                {
                    fprintf(stderr, "the value %d in group %d of line %s appears more than once\n", k+1, j+1, line_header);
                    return 1;
                }
            }
            
            
        }
        
    }
    
    
    return 0;
}


int check_p(FILE *fp)
{
    char * line_header = (char *)"P=";
    int p_values[32];
    int values_frequency[32];
    
    int i = 0;
    
    for (i=0; i<32; i++)
    {
        values_frequency[i] = 0;
    }
    
    if (check_line_format(fp, p_values, line_header, 32))
    {
        return 1;
    }
    
    /*
    for (i=0; i<32; i++)
    {
        printf("%2d ", p_values[i]);
    }
    printf("\n");
    */
    
    for (i=0; i<32; i++)
    {
        if (p_values[i]<1 || p_values[i]>32)
        {
            fprintf(stderr, "the values in line %s are not between 1 to 32\n", line_header);
            return 1;
        }
        else
        {
            values_frequency[p_values[i]-1]++;
        }
    }
    
    for (i=0; i<32; i++)
    {
        if (values_frequency[i] != 1)
        {
            fprintf(stderr, "%d in line %s does not appear once\n",i+1, line_header);
            return 1;
        }
    }
    
    
    
    
    
    return 0;
}


int check_e(FILE *fp)
{
    char * line_header = (char *)"E=";
    int e_values[48];
    int values_frequency[32];
    
    int i = 0;
    
    for(i=0; i<32; i++)
    {
        values_frequency[i] = 0;
    }
    
    if (check_line_format(fp, e_values, line_header, 48))
    {
        return 1;
    }
    
    /*
    for (i=0; i<48; i++)
    {
        printf("%2d ", e_values[i]);
    }
    printf("\n");
    */
    
    for (i=0; i<48; i++)
    {
        if (e_values[i]<1 || e_values[i]>32)
        {
            fprintf(stderr, "the values in line %s are not between 1 to 32\n", line_header);
            return 1;
        }
        else
        {
            values_frequency[e_values[i]-1]++;
        }
    }
    
    for (i=0; i<32; i++)
    {
        if (values_frequency[i] == 0 || values_frequency[i]>2)
        {
            fprintf(stderr, "%d in line %s does not appear once or twice\n",i+1, line_header);
            return 1;
        }
        if (values_frequency[i] != 1)
        {
            if (values_frequency[i] != 2)
            {
                fprintf(stderr, "%d in line %s does not appear once or twice\n",i+1, line_header);
                return 1;
            }
        }
    }
    
    
    return 0;
}


int check_ip(FILE *fp)
{
    char * line_header = (char *)"IP=";
    int ip_values[64];
    int values_frequency[64];
    int i = 0;
    
    for(i=0; i<64; i++)
    {
        values_frequency[i] = 0;
    }
    
    
    if (check_line_format(fp, ip_values, line_header, 64) == 1)
    {
        return 1;
    }
    
    /*
    for (i=0; i<64; i++)
    {
        printf("%2d ", ip_values[i]);
    }
    printf("\n");
    */
    
    for (i=0; i<64; i++)
    {
        if (ip_values[i]<1 || ip_values[i]>64)
        {
            fprintf(stderr, "the values in line %s are not between 1 to 64\n", line_header);
            return 1;
        }
        else
        {
            values_frequency[ip_values[i]-1]++;
        }
    }
    
    for (i=0; i<64; i++)
    {
        if (values_frequency[i] != 1)
        {
            fprintf(stderr, "%d in line %s does not appear once\n",i+1, line_header);
            return 1;
        }
    }
    
    
    return 0;
}


int tablecheck(FILE *fp)
{
    if(check_ip(fp) == 1)
    {
        fprintf(stderr, "IP format error\n");
        return 1;
    }
    //printf("IP format correct\n");
    
    if (check_e(fp) == 1)
    {
        fprintf(stderr, "E format error\n");
        return 1;
    }
    //printf("E format correct\n");
    
    if (check_p(fp) == 1)
    {
        fprintf(stderr, "P format error\n");
        return 1;
    }
    //printf("P format correct\n");
    
    if (check_s(fp) == 1)
    {
        fprintf(stderr, "S format error\n");
        return 1;
    }
    //printf("All S format correct\n");
    
    if (check_v(fp) == 1)
    {
        fprintf(stderr, "V format error\n");
        return 1;
    }
    //printf("V format correct\n");
    
    if (check_pc1(fp) == 1)
    {
        fprintf(stderr, "PC1 format error\n");
        return 1;
    }
    //printf("PC1 format correct\n");
    
    if (check_pc2(fp) == 1)
    {
        fprintf(stderr, "PC2 format error\n");
        return 1;
    }
    //printf("PC2 format correct\n");
    
    //printf("this is function tablecheck\n");
    return 0;
}
