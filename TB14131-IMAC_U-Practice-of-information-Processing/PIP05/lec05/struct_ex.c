#include <stdio.h>

#define NAME_LEN 100

/* Definiton of structure person */
struct person{
    char name[NAME_LEN];
    double height;
    double weight;
};

int main()
{   
    /* (1) variable declaration */
    struct person member;
    
    /* (2) processing contents */
    /* data input */
    printf("Name? ");
    scanf("%s", member.name);
    /* Name with blank characters */
    /*
    fgets(member.name, sizeof(member.name),stdin);
    */
    printf("Height? ");
    scanf("%lf", &member.height);
    printf("Weight? ");
    scanf("%lf", &member.weight);
    
    /* data display */
    printf("----------------------------\n");
    printf("Name:   %s\n",member.name);
    printf("Height: %.1f\n",member.height);
    printf("Weight: %.1f\n",member.weight);
    
	return 0;
}