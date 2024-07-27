/*
1.2 Aim of the program: Given an array arr[] of size N, find the prefix sum of the array. A prefix sum array is another array prefixSum[] of the same size, such that the value of prefixSum[i] is + arr[l] + arr[21 ... arr[i].
*/
#include <stdio.h>

int main() {
    int N;
    printf("Enter the size of array: ");
    scanf("%d", &N);
    
    int arr[N], prefixSum[N];

    printf("Enter the values in array:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        prefixSum[i] = (i == 0) ? arr[i] : prefixSum[i-1] + arr[i];
    }
    
    printf("prefix sum are:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", prefixSum[i]);
    }
    
    return 0;
}
