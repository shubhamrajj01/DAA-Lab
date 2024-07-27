#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_ELEMENTS 300
#define MAX_ELEMENTS 500

void writeAscendingData() {
    FILE *file = fopen("inAsce.dat", "w");
    if (file) {
        int numElements = MIN_ELEMENTS + rand() % (MAX_ELEMENTS - MIN_ELEMENTS + 1);
        for (int i = 1; i <= numElements; i++) {
            fprintf(file, "%d ", i);
        }
        fclose(file);
    } else {
        printf("Error creating file inAsce.dat\n");
    }
}

void writeDescendingData() {
    FILE *file = fopen("inDesc.dat", "w");
    if (file) {
        int numElements = MIN_ELEMENTS + rand() % (MAX_ELEMENTS - MIN_ELEMENTS + 1);
        for (int i = numElements; i >= 1; i--) {
            fprintf(file, "%d ", i);
        }
        fclose(file);
    } else {
        printf("Error creating file inDesc.dat\n");
    }
}

void writeRandomData() {
    FILE *file = fopen("inRand.dat", "w");
    if (file) {
        int numElements = MIN_ELEMENTS + rand() % (MAX_ELEMENTS - MIN_ELEMENTS + 1);
        for (int i = 0; i < numElements; i++) {
            fprintf(file, "%d ", rand() % 1000); // Random numbers between 0 and 999
        }
        fclose(file);
    } else {
        printf("Error creating file inRand.dat\n");
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    writeAscendingData();
    writeDescendingData();
    writeRandomData();

    printf("Data written to files successfully.\n");
    return 0;
}
