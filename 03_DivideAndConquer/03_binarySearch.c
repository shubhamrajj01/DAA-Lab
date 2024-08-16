/*Write a C program that takes an array of integers as input, sorts the array, and then
searches for a target element using the binary search algorithm.
   Sample Input/Output 1:
Input:
Enter the number of elements in the array: 6
Enter the elements of the array:
15 3 9 12 7 1
Enter the target element to search: 9
Output:
Element found at index: 3
Sample Input/Output 2:
Input:
Enter the number of elements in the array: 5
Enter the elements of the array:
4 2 10 6 8
Enter the target element to search: 5
Output:
Element not found in the array */


#include <stdio.h>
void sortArray(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
int binarySearch(int arr[], int size, int target)
{
    int left = 0, right = size - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
        {
            return mid;
        }
        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}
int main()
{
    int size, target;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    sortArray(arr, size);
    printf("Enter the target element to search: ");
    scanf("%d", &target);
    int result = binarySearch(arr, size, target);
    if (result != -1)
    {
        printf("Element found at index: %d\n", result);
    }
    else
    {
        printf("Element not found in the array\n");
    }
    return 0;
}