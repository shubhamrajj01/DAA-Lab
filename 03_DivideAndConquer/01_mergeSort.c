/*
3.1 Aim of the program: Write a menu driven program to sort list of array elements using Merge Sort technique and calculate the execution time only to sort the elements.  Count the number of comparisons.
Note#
●To calculate execution time, assume that single program is under execution in the CPU.
●Number of elements in each input file should vary from 300 to 500 entries.
●For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40….., Store the result in “outMergeAsce.dat”.
●For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60…., Store the result in “outMergeDesc.dat”.
●For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 …, Store the result in “outMergeRand.dat”

Sample Input from file:
MAIN MENU (MERGE SORT)
1. Ascending Data
2. Descending Data
3. Random Data
4. ERROR (EXIT)

Output:
Enter option: 1
Before Sorting: Content of the input file
After Sorting: Content of the output file
Number of Comparisons: Actual
Execution Time: lapse time in nanosecond
*/

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

int comparison_count = 0;

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        comparison_count++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
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
    clock_gettime(CLOCK_REALTIME, &start);
    
    mergeSort(arr, 0, size - 1);

    clock_gettime(CLOCK_REALTIME, &end);
    long execution_time = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);

    writeFile(outputFile, arr, size);

    printf("After Sorting: ");
    printArray(arr, size);
    printf("Number of Comparisons: %d\n", comparison_count);
    printf("Execution Time: %ld nanoseconds\n", execution_time);

    return 0;
}
