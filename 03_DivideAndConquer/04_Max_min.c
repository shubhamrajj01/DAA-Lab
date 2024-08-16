/*Q2. find the maximum and minimum elements in an array using the Divide and
Conquer approach in C using function.
Sample inoput output :
Input:
Enter the number of elements in the array: 7
Enter the elements of the array:
3 17 9 24 2 15 6
Output:
Maximum element: 24
Minimum element: 2
Input:
Enter the number of elements in the array: 5
Enter the elements of the array: -4 0 7 -3 5
Output:
Maximum element: 7
Minimum element: -4
*/

#include <stdio.h>

void findMaxMin(int arr[], int low, int high, int *max, int *min)
{
    if (low == high)
    {
        *max = *min = arr[low];
        return;
    }

    if (low == high - 1)
    {
        if (arr[low] > arr[high])
        {
            *max = arr[low];
            *min = arr[high];
        }
        else
        {
            *max = arr[high];
            *min = arr[low];
        }
        return;
    }

    int mid = (low + high) / 2;
    int max1, min1;

    findMaxMin(arr, low, mid, max, min);
    findMaxMin(arr, mid + 1, high, &max1, &min1);

    if (max1 > *max)
        *max = max1;
    if (min1 < *min)
        *min = min1;
}

int main()
{
    int size;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    int max, min;
    findMaxMin(arr, 0, size - 1, &max, &min);

    printf("Maximum element: %d\n", max);
    printf("Minimum element: %d\n", min);
    return 0;
}


