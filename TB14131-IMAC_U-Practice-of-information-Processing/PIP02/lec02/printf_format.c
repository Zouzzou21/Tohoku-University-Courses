
#include <stdio.h>

int main()
{
    /**** variable declaration ****/
    int int_num = 1234;
    double real_num = 123.456;
    
    /**** precessing contents ****/
    printf("d    |%d|\n", int_num);
    printf("8d   |%8d|\n", int_num);
    printf("-8d  |%-8d|\n", int_num);
    printf("+8d  |%+8d|\n", int_num);
    printf("08d  |%08d|\n", int_num);
    
    printf("f    |%f|\n", real_num);
    printf("12f  |%12f|\n", real_num);
    printf("9.2f |%9.2f|\n", real_num);
    printf(".1f  |%.1f|\n", real_num);
    
    return 0;
}


