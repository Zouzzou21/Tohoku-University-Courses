/*
 file_write.c
file output samples
 */

#include <stdio.h>

int main(void)
{
    FILE *fp;
    char str[] = "I got it\n";
    char str2[] = "an apple";
    int i;

    fp = fopen("sample_out.txt","w");

    /* fputc example */
    for(i=0;str[i]!='\0';i++){
        fputc(str[i],fp);
    }

    /* fputs example */
    fputs(str, fp);

    /* fprintf example (same as fputs) */
    fprintf(fp,"%s",str);

    /* fprintf example（formatted output）*/
    fprintf(fp, "I got %s\n", str2);

    fclose(fp);
    
    return 0;
        
}


