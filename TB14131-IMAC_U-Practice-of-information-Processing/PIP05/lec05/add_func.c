/*
 User-defined function add_func
 */

#include <stdio.h>

/* User-defined add_func */
int add_func(int x, int y)
{
    /* (1)variable declaration */
    int a;
    /* (2)processing contents */
    a = x + y;
    
    /* return value */
    return a;
}

int main()
{

    /* (1) variable declaration */
    int p,q;
    
    /* (2) processing contents */
    q = 2;
    p = add_func(q, 3);
    printf("%d\n", p);
    
	return 0;
}


