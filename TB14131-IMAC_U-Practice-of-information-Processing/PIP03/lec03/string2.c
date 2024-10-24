/*
 Display strings string2.c
 General keyboard input
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

    /* Input of strings */
    /* General kefborad input without scanf*/
    fgets(str, sizeof(str),stdin);


    /* Display strings as array */
    /* str[n] is NOT '\0', repeat display */
    while (str[n] != '\0') {
        printf("str[%d]=%c(0x%02x)\n",n,str[n],str[n]);
        n++;
        if(n >= LEN){
            break;
        }
    }

	return 0;

}
