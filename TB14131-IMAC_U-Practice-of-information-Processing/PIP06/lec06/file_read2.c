/*
 file_read2.c
 sample of file input（use of fgets）
 */

#include <stdio.h>

int main(void)
{
    FILE *fp;
    int code;
    char buf[256];
    
    fp = fopen("sample_read2.txt","r");
    
    if(fp == NULL){
        printf("Can't open file\n");
        return 1;
    }
    
    // /* fgetcの例 */
    while((code = fgetc(fp)) != EOF){
        printf("%c",code);
    }

    /* fgetsの例 */
    while(fgets(buf, sizeof(buf), fp)!= NULL){
        printf("%s",buf); //\n is not necessary
    }
    

    fclose(fp);
    
    return 0;
        
}


