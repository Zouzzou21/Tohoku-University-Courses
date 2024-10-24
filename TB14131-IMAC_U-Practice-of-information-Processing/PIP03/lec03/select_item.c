#include <stdio.h>

int main(void)
{
    /* (1) variable declaration */
    char item;
    
    /* (2) processing contents */
    printf("Select item [a/b/c]: ");
    
    scanf("%c",&item);
    
    switch (item){
        case 'a':
            printf("a is selected\n");
            break;
        case 'b':
            printf("b is selecetd\n");
            break;
        case 'c':
            printf("c is selected\n");
            break;
        default:
            printf("Othen than a,b and c is selected\n");
    }
    return 0;
    
}
