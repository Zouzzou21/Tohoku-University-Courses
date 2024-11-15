#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 17
#define DATA_LEN 100

/* team score structure */
struct team_score {
    char name[NAME_LENGTH]; /* team name */
    int win;                /* number of wins */
    int draw;               /* number of draws */
    int loss;               /* number of losses */
    int GF;                 /* goals for (scored) */
    int GA;                 /* goals against (conceded) */
    int score;              /* win points */
    int point_diff;         /* goal difference */
};

typedef struct team_score SC; /* Alias "SC" for struct team_score */

/* Function prototypes */
void read_data(FILE *fin, SC *table, int team_num);
void calc_score(SC *team);
void rank_score(SC *table, int team_num);
void write_data(FILE *fout, SC *table, int team_num);
void swap_SC(SC *team1, SC *team2);
int count_teams(FILE *fin);
void heapify(SC *table, int team_num, int i);

int main(void) {
    FILE *fin, *fout;
    int team_num;
    SC *table;

    /* Open the CSV file for reading */
    if ((fin = fopen("J_dataset.csv", "r")) == NULL) {
        printf("Can't open input file\n");
        return 1;
    }

    /* Count the number of teams in the CSV */
    team_num = count_teams(fin);
    rewind(fin);  // Reset file pointer to the beginning for reading data

    /* Allocate memory for the team data array */
    table = (SC *)malloc(team_num * sizeof(SC));
    if (table == NULL) {
        printf("Memory allocation failed\n");
        fclose(fin);
        return 1;
    }

    /* Open the output file for writing */
    if ((fout = fopen("J_score.txt", "w")) == NULL) {
        printf("Can't open output file\n");
        fclose(fin);
        free(table);
        return 1;
    }

    /* Read data from CSV */
    read_data(fin, table, team_num);

    /* Calculate scores for each team */
    for (int i = 0; i < team_num; i++) {
        calc_score(&table[i]);
    }

    /* Sort teams by ranking */
    rank_score(table, team_num);

    /* Write the sorted ranking to the output file */
    write_data(fout, table, team_num);

    /* Clean up and close files */
    fclose(fin);
    fclose(fout);
    free(table);

    return 0;
}


/* Function to read data from the CSV file into the table array */
void read_data(FILE *fin, SC *table, int team_num) {
    char buff[DATA_LEN];
    int i = 0;

    while (fgets(buff, sizeof(buff), fin) != NULL && i < team_num) {
        sscanf(buff, "%[^,],%d,%d,%d,%d,%d",
               table[i].name, &table[i].win, &table[i].draw, &table[i].loss,
               &table[i].GF, &table[i].GA);
        i++;
    }
}

/* Function to calculate win points and goal difference for a team */
void calc_score(SC *team) {
    team->score = (team->win * 3) + (team->draw * 1); // Points calculation
    team->point_diff = team->GF - team->GA;           // Goal difference
}

/* Function to rank teams by score, goal difference, and goals for */
void rank_score(SC *table, int team_num) {
    // Build heap
    for (int i = team_num / 2 - 1; i >= 0; i--) {
        heapify(table, team_num, i);
    }

    // One by one extract an element from the heap
    for (int i = team_num - 1; i > 0; i--) {
        swap_SC(&table[0], &table[i]); // Move current root to end
        heapify(table, i, 0);          // Call max heapify on the reduced heap
    }
}

/* Function to write the sorted ranking to the output file */
void write_data(FILE *fout, SC *table, int team_num) {
    fprintf(fout, "Ranking   Team            Wins  Draws  Losses  GF    GA    Points  GD\n");
    fprintf(fout, "--------------------------------------------------------------------\n");
    for (int i = 0; i < team_num; i++) {
        fprintf(fout, "%-9d %-15s %5d %5d %5d %5d %5d %7d %5d\n",
                i + 1, table[i].name, table[i].win, table[i].draw, table[i].loss,
                table[i].GF, table[i].GA, table[i].score, table[i].point_diff);
    }
}


/* Function to swap two teams in the table array */
void c(SC *team1, SC *team2) {
    SC temp = *team1;
    *team1 = *team2;
    *team2 = temp;
}

/* Function to count the number of teams in the CSV file */
int count_teams(FILE *fin) {
    int count = 0;
    char buff[DATA_LEN];

    while (fgets(buff, sizeof(buff), fin) != NULL) {
        count++;
    }
    return count;
}


/* Heapifies a subtree rooted with node i in an array of SC structures, ensuring the max-heap property */
void heapify(SC *table, int team_num, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare left child
    if (left < team_num && 
        (table[left].score > table[largest].score ||
         (table[left].score == table[largest].score && table[left].point_diff > table[largest].point_diff) ||
         (table[left].score == table[largest].score && table[left].point_diff == table[largest].point_diff && table[left].GF > table[largest].GF))) {
        largest = left;
    }

    // Compare right child
    if (right < team_num && 
        (table[right].score > table[largest].score ||
         (table[right].score == table[largest].score && table[right].point_diff > table[largest].point_diff) ||
         (table[right].score == table[largest].score && table[right].point_diff == table[largest].point_diff && table[right].GF > table[largest].GF))) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap_SC(&table[i], &table[largest]);
        heapify(table, team_num, largest); // Recursively heapify the affected subtree
    }
}