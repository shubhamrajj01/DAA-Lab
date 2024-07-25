/*
1.3 Aim of the program.• Write a program to read 'n' integers
from a disc file that must contain some duplicate values and
store them into an array. Perform the following operations on the
array.
a) Find out the total number of duplicate elements.
b) Find out the most repeating element in the array.
Input:
Enter how many numbers you want to read from file: 15
Output:
The content of the array: 10 40 35 47 68 22 40 10 98 10 50 35 68 40 10
Total number of duplicate values = 4
The most repeating element in the array = 10
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void read_numbers_from_file(const char *file_name, int arr[], int n, int *actual_size) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    for (*actual_size = 0; *actual_size < n && fscanf(file, "%d", &arr[*actual_size]) != EOF; (*actual_size)++);
    fclose(file);
}

int count_duplicate_elements(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

int most_repeating_element(int arr[], int size) {
    int max_count = 0, most_repeating = arr[0];
    for (int i = 0; i < size; i++) {
        int count = 1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) count++;
        }
        if (count > max_count) {
            max_count = count;
            most_repeating = arr[i];
        }
    }
    return most_repeating;
}

int main() {
    int n, arr[MAX_SIZE], actual_size;
    
    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);
    
    read_numbers_from_file("input3.txt", arr, n, &actual_size);
    
    if (actual_size == 0) {
        printf("No numbers read from the file.\n");
        return 0;
    }
    
    printf("Numbers read from file: ");
    for (int i = 0; i < actual_size; i++) printf("%d ", arr[i]);
    printf("\n");

    printf("Total number of duplicate elements: %d\n", count_duplicate_elements(arr, actual_size));
    printf("Most repeating element: %d\n", most_repeating_element(arr, actual_size));

    return 0;
}
