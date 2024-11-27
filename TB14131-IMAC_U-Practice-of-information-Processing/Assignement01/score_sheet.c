#include <stdio.h>
#include <math.h>

/* Macro definitions */
#define ID_NUM 10
#define SUB_NUM 3

/* Function prototypes */
float calculateAverage(int scores[], int size);
float calculateDeviation(int scores[], int size, float mean);
float calculateTotalAverage(int totalScores[], int size);
char getRank(int total);
void giveFeedback(int scores[]);
void bubbleSort(int totalScores[], int ids[], int size);

int main() {
    /* Student scores */
    int score[ID_NUM][SUB_NUM] = {
        {80, 94, 84}, {70, 71, 60}, {65, 83, 73},
        {75, 80, 65}, {78, 88, 83}, {92, 100, 98},
        {82, 88, 93}, {79, 85, 80}, {88, 95, 90}, {66, 70, 72}
    };

    int totalScores[ID_NUM], ids[ID_NUM];
    float subjectAvg[SUB_NUM], subjectDev[SUB_NUM];
    float averageTotalScore;
    int id, total = 0;
    float average;

    /* Calculate total scores and store IDs for sorting */
    for (int i = 0; i < ID_NUM; i++) {
        totalScores[i] = 0;
        ids[i] = i;  // Store IDs for sorting
        for (int j = 0; j < SUB_NUM; j++) {
            totalScores[i] += score[i][j];
        }
    }

    /* Calculate average and deviation for each subject */
    for (int j = 0; j < SUB_NUM; j++) {
        int subjectScores[ID_NUM];
        for (int i = 0; i < ID_NUM; i++) {
            subjectScores[i] = score[i][j];
        }
        subjectAvg[j] = calculateAverage(subjectScores, ID_NUM);
        subjectDev[j] = calculateDeviation(subjectScores, ID_NUM, subjectAvg[j]);
    }

    /* Calculate the averaged total score (all students' total scores) */
    averageTotalScore = calculateTotalAverage(totalScores, ID_NUM);

    /* Sort students by total score */
    bubbleSort(totalScores, ids, ID_NUM);

    /* Display the sorted rankings */
    printf("Student Rankings (based on total scores):\n");
    printf("Rank  ID  Total  Rank\n");
    for (int i = 0; i < ID_NUM; i++) {
        printf("%3d   %2d   %3d    %c\n", 
               i + 1, ids[i], totalScores[i], getRank(totalScores[i]));
    }
    printf("\n");

    /* Display average scores for each subject */
    printf("Averaged Scores for Each Subject:\n");
    for (int j = 0; j < SUB_NUM; j++) {
        printf("SUB%d: %.2f\n", j + 1, subjectAvg[j]);
    }
    printf("Averaged Total Score (All Students): %.2f\n\n", averageTotalScore);

    /* Prompt user for student ID */
    printf("Enter student ID (0-9): ");
    scanf("%d", &id);

    if (id < 0 || id >= ID_NUM) {
        printf("Invalid ID. Please enter a value between 0 and 9.\n");
        return 1;
    }

    /* Display score sheet for the given student */
    printf("\nScore Sheet for Student ID: %d\n", id);
    printf("SUB1  SUB2  SUB3  Total  Average  Rank\n");

    /* Calculate total and average for the selected student */
    for (int j = 0; j < SUB_NUM; j++) {
        total += score[id][j];
    }
    average = total / (float)SUB_NUM;

    /* Display individual scores, total, average, and rank */
    printf("%3d   %3d   %3d   %3d   %.2f    %c\n", 
           score[id][0], score[id][1], score[id][2], 
           total, average, getRank(total));

    /* Provide feedback */
    giveFeedback(score[id]);

    /* Display deviation values */
    printf("\nDeviation values for Student ID %d:\n", id);
    for (int j = 0; j < SUB_NUM; j++) {
        float deviation = (score[id][j] - subjectAvg[j]) / subjectDev[j];
        printf("SUB%d: %.2f\n", j + 1, deviation);
    }

    return 0;
}

/* Function to calculate the average score */
float calculateAverage(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / (float)size;
}

/* Function to calculate the standard deviation */
float calculateDeviation(int scores[], int size, float mean) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        float diff = scores[i] - mean;
        sum += diff * diff;
    }
    return sqrt(sum / size);
}

/* Function to calculate the averaged total score */
float calculateTotalAverage(int totalScores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += totalScores[i];
    }
    return sum / (float)size;
}

/* Function to determine rank based on total score */
char getRank(int total) {
    if (total >= 270) return 'A';
    else if (total >= 240) return 'B';
    else if (total >= 210) return 'C';
    else return 'D';
}

/* Function to provide feedback based on the scores */
void giveFeedback(int scores[]) {
    printf("Feedback: ");
    if (scores[0] < 70) printf("Improve in SUB1. ");
    if (scores[1] < 70) printf("Improve in SUB2. ");
    if (scores[2] < 70) printf("Improve in SUB3. ");
    if (scores[0] >= 70 && scores[1] >= 70 && scores[2] >= 70) 
        printf("Good performance overall!");
    printf("\n");
}

/* Bubble sort to rank students based on total scores */
void bubbleSort(int totalScores[], int ids[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (totalScores[j] < totalScores[j + 1]) {
                /* Swap scores */
                int temp = totalScores[j];
                totalScores[j] = totalScores[j + 1];
                totalScores[j + 1] = temp;

                /* Swap corresponding IDs */
                temp = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = temp;
            }
        }
    }
}
