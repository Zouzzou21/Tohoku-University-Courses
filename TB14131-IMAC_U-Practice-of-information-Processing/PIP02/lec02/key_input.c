#include <stdio.h>

int main(){
    
    /**** variable declaration ****/
    int x, y;           /* integer type */
    
    /**** processing contents ****/
    printf("Input two numbers: ");
    
    /* Get keyboard input */
    scanf("%d %d", &x, &y);
    
    /* display getting value */
    printf("x=%d\n", x);
    printf("y=%d\n", y);
    
    return 0;
}
