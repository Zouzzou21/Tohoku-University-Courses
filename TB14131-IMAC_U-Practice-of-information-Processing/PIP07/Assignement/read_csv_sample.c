/* 
    J_score_file.c
    Japanese football league score 
    read & write
 */

#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 15
#define DATA_LEN 100

int main(void)
{
    /* variable declaration */
    FILE *fin;
    char buff[DATA_LEN];
    char name[NAME_LENGTH]; /* team name */
    int win;  /* number of wins */
    int draw; /* number of draws */
    int loss; /* number of loses */
    int GF;   /* goals for (total goals scored)*/
    int GA;   /* goals against (total goals conceded) */
    
    if((fin = fopen("J_dataset.csv","r"))==NULL){ //open csv file
        printf("Can't open file\n");
        exit(1);
    }
 
    printf("      team name         win  draw  lose   GF    GA  \n");

    while(fgets(buff, sizeof(buff), fin) != NULL){ /*read one line from file*/
        
        /* format matching for one line read */
        sscanf(buff,"%[^,],%d,%d,%d,%d,%d", name, &win, &draw, &loss, &GF, &GA);
        
        /* one line display out */
        printf("%20s %5d %5d %5d %5d %5d\n", name, win, draw, loss, GF, GA);

    }

    fclose(fin);  /* close input file */

    return(0);
}
