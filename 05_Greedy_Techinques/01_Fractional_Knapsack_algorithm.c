#include <stdio.h>  
#include <stdlib.h>  
  
// Structure to represent an item  
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
  
// Function to heapify the array  
void heapify(ITEM arr[], int n, int i) {  
   int largest = i;  // Initialize largest as root  
   int left = 2 * i + 1;  // left = 2*i + 1  
   int right = 2 * i + 2;  // right = 2*i + 2  
  
   // If left child is larger than root  
   if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)  
      largest = left;  
  
   // If right child is larger than largest so far  
   if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)  
      largest = right;  
  
   // If largest is not root  
   if (largest!= i) {  
      swap(&arr[i], &arr[largest]);  
      // Recursively heapify the affected sub-tree  
      heapify(arr, n, largest);  
   }  
}  
  
// Function to perform heap sort  
void heapSort(ITEM arr[], int n) {  
   // Build heap (rearrange array)  
   for (int i = n / 2 - 1; i >= 0; i--)  
      heapify(arr, n, i);  
  
   // One by one extract elements from heap  
   for (int i = n - 1; i > 0; i--) {  
      // Move current root to end  
      swap(&arr[0], &arr[i]);  
      // call max heapify on the reduced heap  
      heapify(arr, i, 0);  
   }  
}  
  
// Function to calculate the maximum profit using fractional knapsack  
void fractionalKnapsack(ITEM items[], int n, float capacity) {  
   heapSort(items, n);  // Sort items by profit/weight ratio  
  
   float total_profit = 0.0;  
   printf("Item No\tProfit\tWeight\tAmount to be taken\n");  
  
   for (int i = 0; i < n; i++) {  
      if (capacity >= items[i].item_weight) {  
        // Take the whole item  
        capacity -= items[i].item_weight;  
        total_profit += items[i].item_profit;  
        printf("%d\t%.6f\t%.6f\t1.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);  
      } else {  
        // Take the fraction of the remaining item  
        float fraction = capacity / items[i].item_weight;  
        total_profit += items[i].item_profit * fraction;  
        printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);  
        break;  // The knapsack is full now  
      }  
   }  
   printf("Maximum profit: %.6f\n", total_profit);  
}  
  
int main() {  
   int n;  
   float capacity;  
  
   // Read the number of items  
   printf("Enter the number of items: ");  
   scanf("%d", &n);  
  
   // Allocate memory for items  
   ITEM *items = (ITEM *)malloc(n * sizeof(ITEM));  
   if (items == NULL) {  
      fprintf(stderr, "Memory allocation failed\n");  
      return 1;  
   }  
  
   // Read the profit and weight of each item  
   for (int i = 0; i < n; i++) {  
      items[i].item_id = i + 1;  
      printf("Enter the profit and weight of item no %d: ", i + 1);  
      scanf("%f %f", &items[i].item_profit, &items[i].item_weight);  
      items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;  
   }  
  
   // Read the knapsack capacity  
   printf("Enter the capacity of the knapsack: ");  
   scanf("%f", &capacity);  
  
   // Calculate the maximum profit using fractional knapsack  
   fractionalKnapsack(items, n, capacity);  
  
   // Free allocated memory  
   free(items);  
  
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