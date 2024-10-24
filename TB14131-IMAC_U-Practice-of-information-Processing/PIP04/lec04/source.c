/*
 score.c
 */

#include <stdio.h>

/* Macro definition */
#define ID_NUM 10
#define SUB_NUM 3

int main(){
    
    /**** (1) variable declaration ****/
    int score[ID_NUM][SUB_NUM]={{80,94,84},{70,71,60},{65,83,73},{75,80,65},{78,88,83},{92,100,98},{82,88,93},{79,85,80},{88,95,90},{66,70,72}};
    
    int i;
    
    /**** (2) processing contents ****/
    /* display scores */
    printf("ID  SUB1  SUB2  SUB3\n");
    for (i = 0; i < ID_NUM; i++){
        printf("[%d]  %3d   %3d   %3d\n", i, score[i][0], score[i][1], score[i][2]);
    }
    
    return 0;
    
}