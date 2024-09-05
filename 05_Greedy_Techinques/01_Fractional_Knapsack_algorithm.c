#include <stdio.h>

// Structure definition for ITEM
typedef struct {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
} ITEM;

// Function to swap two items
void swap(ITEM *a, ITEM *b) {
    ITEM temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain the heap property
void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Change comparison to make it a max-heap (non-increasing order)
    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap sort function to sort items by profit/weight ratio in non-increasing order
void heapSort(ITEM arr[], int n) {
    // Build a max-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one and maintain heap
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }

    // Reverse the sorted array to get non-increasing order
    for (int i = 0; i < n / 2; i++) {
        swap(&arr[i], &arr[n - i - 1]);
    }
}

// Function to calculate the maximum profit using the Fractional Knapsack algorithm
float fractionalKnapsack(ITEM items[], int n, float capacity) {
    heapSort(items, n); // Sorting items by profit/weight ratio

    float total_profit = 0.0;
    printf("Item No\tProfit\tWeight\tAmount to be taken\n");

    for (int i = 0; i < n; i++) {
        if (capacity == 0)
            break;

        if (items[i].item_weight <= capacity) {
            capacity -= items[i].item_weight;
            total_profit += items[i].item_profit;
            printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, 1.0);
        } else {
            float fraction = capacity / items[i].item_weight;
            total_profit += items[i].item_profit * fraction;
            printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            capacity = 0;
        }
    }

    return total_profit;
}

int main() {
    int n;
    float capacity;

    // Input number of items and knapsack capacity
    printf("Enter the number of items: ");
    scanf("%d", &n);

    ITEM items[n];

    // Input profit and weight of each item
    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    // Calculate and display maximum profit
    float max_profit = fractionalKnapsack(items, n, capacity);
    printf("Maximum profit: %.6f\n", max_profit);

    return 0;
}


/*
Write a program to find the maximum profit nearest to but not exceeding the given knapsack capacity using the Fractional Knapsack algorithm. Notes# Declare a structure ITEM having data members item_id, item_profit, item_weight and profit_weight_ratio. Apply heap sort technique to sort the items in non-increasing order, according to their profit /weight.
Input:
Enter the number of items: 3
Enter the profit and weight of item no 1: 27 16
Enter the profit and weight of item no 2: 14 12
Enter the profit and weight of item no 3: 26 13
Enter the capacity of knapsack:18
Output:
Item No profit Weight Amount to be taken
3 26.000000 13.000000 1.000000
1 27.000000 16.000000 0.312500
2 14.000000 12.000000 0.000000
Maximum profit:34.437500*/