/*
 shows address of variable s and arrays
 */

#include <stdio.h>

int main(){
    
    int    a;
    double b;
    int    c[3];
    double d[3];    
    /**** processing contents****/
    printf("-----------------------------------\n");
    printf("address of int type a    :%p\n", &a);
    printf("address of double type b :%p\n", &b);
    printf("-----------------------------------\n");
    printf("size of int type         :%ld\n", sizeof(a));
    printf("size of double type      :%ld\n", sizeof(b));
    printf("-----------------------------------\n");
    printf("address of int type c[0] :%p\n", &c[0]);
    printf("address of int type c[1] :%p\n", &c[1]);
    printf("address of int type c[2] :%p\n", &c[2]);
    printf("-----------------------------------\n");
    printf("address of int type d[0] :%p\n", &d[0]);
    printf("address of int type d[1] :%p\n", &d[1]);
    printf("address of int type d[2] :%p\n", &d[2]);
    return 0;
}  