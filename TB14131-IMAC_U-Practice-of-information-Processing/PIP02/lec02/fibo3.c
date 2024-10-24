/* フィボナッチ数列の例（3）*/
#include <stdio.h>
#include <math.h>
 
int main(void)
{
    /**** 変数宣言 ****/
    int fn, n;
 
     /**** 処理内容 ****/
    n = 8;
    fn = round((pow((1+sqrt(5))/2, n)
            - pow((1-sqrt(5))/2, n))/sqrt(5));

    printf("n=%d: fn=%d\n", n, fn);

   return 0;
}
