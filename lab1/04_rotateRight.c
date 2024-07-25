/*
Aim of the program: Write a function to ROTATE_RIGHT(p1, p2 ) right an array for first p2 elements by 1 position using EXCHANGE(p, q) function that swaps/exchanges the numbers p & q. Parameter p1 be the starting address of the array and p2 be the number of elements to be rotated.  

Input:
Enter an array A of size N (9): 11 22 33 44 55 66 77 88 99 
Call the function ROTATE_RIGHT(A, 5)
Output:
Before ROTATE: 	11 22 33 44 55 66 77 88 99 
After ROTATE: 	55 11 22 33 44 66 77 88 99
 */

#include <stdio.h>
#include <stdlib.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *p1, int p2) {
    for (int i = p2 - 1; i > 0; i--) {
        EXCHANGE(&p1[i], &p1[i - 1]);
    }
}

int main() {
    int N, p2;

    printf("Enter the size of the array (N): ");
    scanf("%d", &N);

    int A[N];

    printf("Enter the elements of the array: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    printf("Enter the number of elements to rotate (p2): ");
    scanf("%d", &p2);

    printf("Before ROTATE:\t");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    ROTATE_RIGHT(A, p2);

    printf("After ROTATE:\t");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    free(A);

    return 0;
}
