/*
 Japanese football league ranking file ouput program
 Template：J_score_template1.c
 */

#include <stdio.h>
#include <stdlib.h>

#define TEAM_NUM 18
#define NAME_LENGTH 15
#define DATA_LEN 100

/* team score structure */
struct team_score{
    char name[NAME_LENGTH]; /* team name */
    int win;  /* number of win */
    int draw; /* number of draw */
    int loss; /* number of lose */
    int GF;   /* goals for (scored)*/
    int GA;   /* goals against (conceded)*/
    int score; /* win points */
    int point_diff; /* goals difference */
};

typedef struct team_score SC; /*strcut team_score is aliased as "SC" */

/* prototype declaration of functions */
void read_data(FILE *fin, SC table[]);
void calc_score(SC *team);
void rank_score(SC table[]);
void swap_SC(SC *team1, SC *team2);
void write_data(FILE *fout, SC table[]);


int main(void)
{
    /* variable declaration */
    FILE *fin, *fout;
    SC table[TEAM_NUM]; /* team_score structure type array for storing data */
    int i;
    
    /* processing contents */
    /* Open reading file */
    if((fin = fopen("J_dataset.csv","r"))==NULL){ // open input file
        printf("Can't open file\n");
        exit(1);
    }
    /* Open writing file */
    fout = fopen("J_score.txt","w"); // open output file
 
 
    
    /* (1) Reading file */
    read_data(fin, table);
    
    
    /* （2）Calculating score */
    for(i=0; i< TEAM_NUM; i++){
        calc_score(&table[i]);
    }

    /* （3）Ranking based on score */
    rank_score(table);
    
    
   /* （4) writing raking file in order*/
    write_data(fout, table);


    /* closing process */
    fclose(fin);  /* close reading file */
    fclose(fout); /* close writing file */

    return(0);
}

/* Reading score file */
void read_data(FILE *fin, SC table[])
{
    /* processing contents
     Read data from the file and assign score into SC structure array table[]
     Note: array 'table' is pointer indicating SC structure type array
     */
}

/* Calculation of winpoints and goals difference */
void calc_score(SC *team)
{
    /* processing contents
     Argument is pointer to SC type structure．
     Reference to member of SC type struture indicated by pointer,
     calculate winpoints and goals difference, and assign them
     into the members score and point_diff of the same structure
     */
}

/* Ranking based on score */
void rank_score(SC table[])
{
    /* processing contents
     Sorting the structure array of the argument based on the member score 
     of structure. Make the function swap_SC to exchange the contents of 
     structures. 
     Note: array name table is pointer indicating SC type structure 
     */
    
}

/* Swaping the contents of structure */
void swap_SC(SC *team1, SC *team2)
{
    /* processing contents
     Reference to the member of structures indicated by
     pointers for two SC type structure, and swapping all 
     the members. 
     */

}


/* Writing ranking file */
void write_data(FILE *fout, SC table[])
{
    /* processing contents
     SC structure type array of argument has already been sorted by score
     and therefore display with format as they are.
     Note： array name table is pointer indicating SC type structure 
     */
}
