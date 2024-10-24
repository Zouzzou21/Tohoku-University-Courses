/*
 Display strings: string.c
 */

#include <stdio.h>

#define LEN 100 /* MACRO definition */

int main()
{

    /**** (1) variable declaration ****/
    char str[LEN];
    int i;
    int n=0;
    
    /**** (2) processing contents ****/
    /* Initialization of array */
    for (i = 0; i < LEN; i++){
        str[i] = 0;
    }
    
    /* Input of strirgs */
    scanf("%s", str);
    
    /* Display strings as array */
    /* str[n] is NOT '\0', repeat display */
    while (str[n] != '\0') {
        printf("str[%d]=%c\n",n,str[n]);
        n++;
        if(n >= LEN){
            break;
        }
    }

	return 0;

}




