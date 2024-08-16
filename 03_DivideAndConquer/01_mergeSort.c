#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 500
#define IN_ASCE "inAsce.dat"
#define OUT_MERGE_ASCE "outMergeAsce.dat"
#define IN_DESC "inDesc.dat"
#define OUT_MERGE_DESC "outMergeDesc.dat"
#define IN_RAND "inRand.dat"
#define OUT_MERGE_RAND "outMergeRand.dat"
#define REPEAT_TIMES 1000  // Number of repetitions

int comparison_count = 0;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparison_count++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void readFile(const char *filename, int arr[], int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
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
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int option;
    int arr[MAX_ELEMENTS];
    int size;
    const char *inputFile = NULL, *outputFile = NULL;

    printf("MAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");
    printf("Enter option: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            inputFile = IN_ASCE;
            outputFile = OUT_MERGE_ASCE;
            break;
        case 2:
            inputFile = IN_DESC;
            outputFile = OUT_MERGE_DESC;
            break;
        case 3:
            inputFile = IN_RAND;
            outputFile = OUT_MERGE_RAND;
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

    for (int i = 0; i < REPEAT_TIMES; i++) {
        // You may need to reset the array to its original state before each sort
        // If sorting in place and you want to repeat, consider creating a copy of the original array
        mergeSort(arr, 0, size - 1);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    long execution_time = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
    execution_time /= REPEAT_TIMES; // Average execution time

    writeFile(outputFile, arr, size);

    printf("After Sorting: ");
    printArray(arr, size);
    printf("Number of Comparisons: %d\n", comparison_count);
    printf("Execution Time: %ld nanoseconds (average over %d repetitions)\n", execution_time, REPEAT_TIMES);

    return 0;
}
