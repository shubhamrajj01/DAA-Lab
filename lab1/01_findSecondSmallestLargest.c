/* Aim of the program: Write a program to find out the second smallest and second largest element stored in an array of n integers.
Input: Size of the array is 'n' and read 'n' number of elements
from a disc file.
Output: Second smallest, Second largest
 */

#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, first_min = INT_MAX, second_min = INT_MAX, first_max = INT_MIN, second_max = INT_MIN;
    FILE *file = fopen("input1.txt", "r");
    fscanf(file, "%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
        if (arr[i] < first_min) {
            second_min = first_min;
            first_min = arr[i];
        } else if (arr[i] < second_min && arr[i] != first_min) {
            second_min = arr[i];
        }
        if (arr[i] > first_max) {
            second_max = first_max;
            first_max = arr[i];
        } else if (arr[i] > second_max && arr[i] != first_max) {
            second_max = arr[i];
        }
    }
    fclose(file);
    printf("Second smallest element: %d\n", second_min);
    printf("Second largest element: %d\n", second_max);
    return 0;
}

