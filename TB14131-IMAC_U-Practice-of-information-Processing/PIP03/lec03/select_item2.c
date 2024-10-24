#include <stdio.h>

int main(void)
{
    /* (1) variable declaration */
    char item;
    
    /* (2) processing contents */
    printf("Select item [a/b/c]: ");
    
    scanf("%c",&item);
    
    if (item == 'a'){
        printf("a is selected\n");
    }else if (item == 'b'){
        printf("b is selected\n");
    }else if (item == 'c'){
        printf("c is selected\n");
    }else{
        printf("Other than a,b and c is selected\n");
    }
    return 0;
    
}
