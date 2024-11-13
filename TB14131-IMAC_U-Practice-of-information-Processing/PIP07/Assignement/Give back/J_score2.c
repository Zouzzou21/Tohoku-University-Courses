#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 15
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
void rank_score(SC *table, SC **rank_array, int team_num);
void write_data(FILE *fout, SC **rank_array, int team_num);
int count_teams(FILE *fin);
void heapify(SC **rank_array, int team_num, int i);

int main(void) {
    FILE *fin, *fout;
    int team_num;
    SC *table;
    SC **rank_array;

    /* Open the CSV file for reading */
    if ((fin = fopen("J_dataset.csv", "r")) == NULL) {
        printf("Can't open input file\n");
        return 1;
    }

    /* Count the number of teams in the CSV */
    team_num = count_teams(fin);
    rewind(fin);  // Reset file pointer to the beginning for reading data

    /* Allocate memory for the team data array and rank pointer array */
    table = (SC *)malloc(team_num * sizeof(SC));
    rank_array = (SC **)malloc(team_num * sizeof(SC *));
    if (table == NULL || rank_array == NULL) {
        printf("Memory allocation failed\n");
        fclose(fin);
        return 1;
    }

    /* Open the output file for writing */
    if ((fout = fopen("J_score2.txt", "w")) == NULL) {
        printf("Can't open output file\n");
        fclose(fin);
        free(table);
        free(rank_array);
        return 1;
    }

    /* Read data from CSV */
    read_data(fin, table, team_num);

    /* Calculate scores for each team and initialize rank array */
    for (int i = 0; i < team_num; i++) {
        calc_score(&table[i]);
        rank_array[i] = &table[i];  // Initialize rank array with pointers to each team
    }

    /* Sort teams by ranking using the rank array */
    rank_score(table, rank_array, team_num);

    /* Write the sorted ranking to the output file */
    write_data(fout, rank_array, team_num);

    /* Clean up and close files */
    fclose(fin);
    fclose(fout);
    free(table);
    free(rank_array);

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

void calc_score(SC *team) {
    team->score = (team->win * 3) + (team->draw * 1); // Points calculation
    team->point_diff = team->GF - team->GA;           // Goal difference
}

void rank_score(SC *table, SC **rank_array, int team_num) {
    // Build heap
    for (int i = team_num / 2 - 1; i >= 0; i--) {
        heapify(rank_array, team_num, i);
    }

    // One by one extract an element from the heap
    for (int i = team_num - 1; i > 0; i--) {
        SC *temp = rank_array[0];
        rank_array[0] = rank_array[i];
        rank_array[i] = temp;

        heapify(rank_array, i, 0); // Call max heapify on the reduced heap
    }
}

void write_data(FILE *fout, SC **rank_array, int team_num) {
    fprintf(fout, "Ranking   Team            Wins  Draws  Losses  GF    GA    Points  GD\n");
    fprintf(fout, "--------------------------------------------------------------------\n");
    for (int i = 0; i < team_num; i++) {
        fprintf(fout, "%-9d %-15s %5d %5d %5d %5d %5d %7d %5d\n",
                i + 1, rank_array[i]->name, rank_array[i]->win, rank_array[i]->draw,
                rank_array[i]->loss, rank_array[i]->GF, rank_array[i]->GA,
                rank_array[i]->score, rank_array[i]->point_diff);
    }
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

void heapify(SC **rank_array, int team_num, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare left child
    if (left < team_num &&
        (rank_array[left]->score > rank_array[largest]->score ||
         (rank_array[left]->score == rank_array[largest]->score && rank_array[left]->point_diff > rank_array[largest]->point_diff) ||
         (rank_array[left]->score == rank_array[largest]->score && rank_array[left]->point_diff == rank_array[largest]->point_diff && rank_array[left]->GF > rank_array[largest]->GF))) {
        largest = left;
    }

    // Compare right child
    if (right < team_num &&
        (rank_array[right]->score > rank_array[largest]->score ||
         (rank_array[right]->score == rank_array[largest]->score && rank_array[right]->point_diff > rank_array[largest]->point_diff) ||
         (rank_array[right]->score == rank_array[largest]->score && rank_array[right]->point_diff == rank_array[largest]->point_diff && rank_array[right]->GF > rank_array[largest]->GF))) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        SC *temp = rank_array[i];
        rank_array[i] = rank_array[largest];
        rank_array[largest] = temp;

        heapify(rank_array, team_num, largest); // Recursively heapify the affected subtree
    }
}