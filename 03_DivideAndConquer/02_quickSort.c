/*
3.2 Aim of the program: Write a menu driven program to sort a list of elements in ascending order using Quick Sort technique. Each choice for the input data has its own disc file.  A separate output file can be used for sorted elements. After sorting display the content of the output file along with number of comparisons. Based on the partitioning position for each recursive call, conclude the input scenario is either best-case partitioning or worst-case partitioning. 
Note# 
●The worst-case behavior for quicksort occurs when the partitioning routine produces one subproblem with n-1 elements and one with 0 elements. The best-case behaviour occurred in most even possible split, PARTITION produces two subproblems, each of size no more than n/2.
●Number of elements in each input file should vary from 300 to 500 entries. 
●For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40….., Store the result in “outQuickAsce.dat”.
●For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60…., Store the result in “outQuickDesc.dat”.
●For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 …, Store the result in “outQuickRand.dat”
Sample Input from file:
MAIN MENU (QUICK SORT)
1. Ascending Data
2. Descending Data
3. Random Data
4. ERROR (EXIT)

Output:
Enter option: 1
Before Sorting: Content of the input file
After Sorting: Content of the output file
Number of Comparisons: Actual
Scenario: Best or Worst-case
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 500

int comparison_count = 0;
int worst_case_flag = 0;

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

    // Check if partition is worst-case
    if (i == low - 1 || i == high - 1) {
        worst_case_flag = 1;
    }

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
    worst_case_flag = 0;

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
    printf("Scenario: %s-case\n", worst_case_flag ? "Worst" : "Best");

    return 0;
}
