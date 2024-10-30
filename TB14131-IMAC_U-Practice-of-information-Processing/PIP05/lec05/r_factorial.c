
#include <stdio.h>

/***** prototype declaration ****/
int fact(int n);

/***** function rfact() ****/
int rfact(int n)
{
    /**** variable declaration ****/
    int m;
    
    /**** processing contents ****/
    /* when n=0（0! = 1）*/
    if (n == 0){
        return 1;
    }
    /* when n=0 */
    m = rfact(n - 1);    // recursive call for rfact(n-1)
    return n * m;
}

/***** main function *****/
int main()
{
    /**** variable declaration ****/
    int num;          /* natural number */
    int ans;          /* answer */
    
    /**** processing contents ****/
    
    /* input of natural number */
    printf("Input natural number = ");
    scanf("%d", &num);

    /* Caluculate factorial of natural number */
    ans = rfact(num);
    
    /* display results */
    printf("%d! = %d\n", num, ans);
    return 0;
}

