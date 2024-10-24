#include <stdio.h>

int main()
{    
    /**** variable declaration ****/
    float x, y, sum, diff, prod, quot;   /* real type */
    char op;
    
    /**** processing contents ****/
    /* assignment */
    printf("Please tap you calcul number one then enter operator enter then second number enter:");
    scanf("%f %c %f", &x, &op, &y);
    switch (op)
    {
    case'+':
        /* sum */
        sum = x + y;
        printf("sum=%.2f\n", sum);
        break;
    case'-': 
        /* diff */
        diff = x - y;
        printf("diff=%.2f\n", diff);
        break;
    case'*': 
        /* prod */
        prod = x * y;
        printf("production=%.2f\n", prod);
        break;
    case'/':
        /* quot */
        if ( y == 0.0){
            printf("quotient is not available\n");
        }else{
            quot = (float)x/y;
            printf("quotient=%.2f\n", quot);
        }
        break;
    
    default:
        break;
    }
    
    return 0;
}
