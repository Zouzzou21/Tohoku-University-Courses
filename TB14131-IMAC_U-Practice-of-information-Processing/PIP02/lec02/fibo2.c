/* フィボナッチ数列の例（2）*/
#include <stdio.h>
 
int fibonacci(int n)
{
    int fn;

    if (n == 1 || n == 2){
        fn = 1;
    }else{
        fn = fibonacci(n-2) + fibonacci(n-1);
    }
    return fn;
}

int main(void)
{
    /**** 変数宣言 ****/
    int fn, n;
    n = 8;
    fn = fibonacci(n);
    printf("n=%d: fn=%d\n", n, fn);

   return 0;
}
