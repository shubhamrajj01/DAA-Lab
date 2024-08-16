#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 500

int comparison_count = 0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

 int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        comparison_count++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}  


void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high); 
    }
}

void readFile(const char *filename, int arr[], int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    *size = 0;
    while (fscanf(file, "%d", &arr[*size]) != EOF && *size < MAX_ELEMENTS) {
        (*size)++;
    }

    fclose(file);
}

void writeFile(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int option;
    int arr[MAX_ELEMENTS];
    int size;
    const char *inputFile, *outputFile;

    printf("MAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");
    printf("Enter option: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            inputFile = "inAsce.dat";
            outputFile = "outQuickAsce.dat";
            break;
        case 2:
            inputFile = "inDesc.dat";
            outputFile = "outQuickDesc.dat";
            break;
        case 3:
            inputFile = "inRand.dat";
            outputFile = "outQuickRand.dat";
            break;
        case 4:
            return 0;
        default:
            printf("Invalid option.\n");
            return 0;
    }

    readFile(inputFile, arr, &size);
    printf("Before Sorting: ");
    printArray(arr, size);

    comparison_count = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    quickSort(arr, 0, size - 1);

    clock_gettime(CLOCK_MONOTONIC, &end);
    long execution_time = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);

    writeFile(outputFile, arr, size);

    printf("After Sorting: ");
    printArray(arr, size);
    printf("Number of Comparisons: %d\n", comparison_count);
    printf("Execution Time: %ld nanoseconds\n", execution_time);

    return 0;
}

