#include <stdio.h>
#include <stdlib.h>

#define MEMBER_NUM 3

typedef struct {
    char name[20];
    int height;
    int weight;
} st_person;

void print_person_id(st_person person[], int id) {
    printf("Name: %s\n", person[id].name);
    printf("Height: %d\n", person[id].height);
    printf("Weight: %d\n", person[id].weight);
}

int main(void) {
    st_person member[MEMBER_NUM] = {
        {"Ichiro", 160, 50},
        {"Jiro", 170, 60},
        {"Saburo", 180, 70}
    };

    int id;

    /* Prompt for ID input */
    printf("ID? ");
    if (scanf("%d", &id) != 1) {
        fprintf(stderr, "Invalid input. Exiting.\n");
        exit(1);
    }

    /* Validate ID and print person details */
    if (id >= 0 && id < MEMBER_NUM) {
        print_person_id(member, id);
    } else {
        fprintf(stderr, "Invalid ID. Please enter a number between 0 and %d.\n", MEMBER_NUM - 1);
        exit(1);
    }

    return 0;
}
