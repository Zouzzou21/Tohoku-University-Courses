/*
 file_read.c
 sample of file input
 */

#include <stdio.h>

int main(void)
{
    FILE *fp;
    char buf[256];
    
    fp = fopen("sample_read2.txt","r");
    
    if(fp == NULL){
        printf("Can't open file\n");
        return 1;
    }
    
    while(fscanf(fp, "%s", buf)!= EOF){
        printf("%s\n",buf);
    }
    
    fclose(fp);
    
    return 0;
        
}


