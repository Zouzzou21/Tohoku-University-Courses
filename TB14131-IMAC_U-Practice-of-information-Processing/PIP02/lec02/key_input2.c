#include <stdio.h>

int main(){
    
    /**** variable declaration ****/
    // int x, y;           /* integer type */
    float x, y;         /* real type */
    
    /**** processing contents ****/
    printf("Input two numbers: \n");
    
    /* Get keyboard input */
    scanf("%f %f", &x, &y);
    
    /* display getting value */
    printf("x=%f\n", x);
    printf("y=%f\n", y);
    
    return 0;
}
