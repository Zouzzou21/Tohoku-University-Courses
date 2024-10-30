/*
 Scope of variable local_grobal.c
 */

#include <stdio.h>

int count;

int add_count(int x)
{
    
    /* variable declaration */
    int count;
    
    /* processing contents */
    count = ++x;
    
    return count;
}


int main()
{
    
    /* variable declaration */
    
    /* processing contents */
    count = 0;
    
    while(1){
        if (count > 10){
            break;
        }
        
        printf("%d\n",count);
        count = add_count(count);
    }
    
    return 0;
}



