#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct person arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void maxHeapify(struct person arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMinHeap(struct person arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

void buildMaxHeap(struct person arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void readData(struct person **arr, int *n) {
    FILE *file = fopen("students.txt", "r");
    if (!file) {
        printf("Error: File not found.\n");
        return;
    }

    fscanf(file, "%d", n);
    *arr = (struct person *)malloc((*n) * sizeof(struct person));

    for (int i = 0; i < *n; i++) {
        (*arr)[i].name = (char *)malloc(50 * sizeof(char)); 
        fscanf(file, "%d %s %d %d %d", &(*arr)[i].id, (*arr)[i].name, &(*arr)[i].age, &(*arr)[i].height, &(*arr)[i].weight);
    }

    fclose(file);
    printf("Data successfully read from file.\n");
}

void displayYoungestWeight(struct person arr[], int n) {
    if (n == 0) {
        printf("Heap is empty.\n");
        return;
    }
    printf("Weight of the youngest student: %.2f kg\n", arr[0].weight * 0.453592); 
}

void insertPerson(struct person arr[], int *n, struct person newPerson) {
    (*n)++;
    arr = (struct person *)realloc(arr, (*n) * sizeof(struct person));
    int i = *n - 1;
    arr[i] = newPerson;

    while (i != 0 && arr[(i - 1) / 2].age > arr[i].age) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    printf("Person inserted into the min-heap.\n");
}

void deleteOldestPerson(struct person arr[], int *n) {
    if (*n <= 0) {
        printf("Heap is empty.\n");
        return;
    }

    if (*n == 1) {
        (*n)--;
        return;
    }

    arr[0] = arr[*n - 1];
    (*n)--;
    minHeapify(arr, *n, 0);

    printf("Oldest person deleted from the min-heap.\n");
}

void displayPersons(struct person arr[], int n) {
    printf("Id\tName\t\tAge\tHeight\tWeight(pound)\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%d\t%d\t%d\n", arr[i].id, arr[i].name, arr[i].age, arr[i].height, arr[i].weight);
    }
}

int main() {
    struct person *arr = NULL;
    int n = 0, option;

    do {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");

        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                readData(&arr, &n);
                displayPersons(arr, n);
                break;
            case 2:
                buildMinHeap(arr, n);
                printf("Min-heap created based on age.\n");
                displayPersons(arr, n);
                break;
            case 3:
                buildMaxHeap(arr, n);
                printf("Max-heap created based on weight.\n");
                displayPersons(arr, n);
                break;
            case 4:
                displayYoungestWeight(arr, n);
                break;
            case 5: {
                struct person newPerson;
                newPerson.name = (char *)malloc(50 * sizeof(char));
                printf("Enter ID, Name, Age, Height, and Weight: ");
                scanf("%d %s %d %d %d", &newPerson.id, newPerson.name, &newPerson.age, &newPerson.height, &newPerson.weight);
                insertPerson(arr, &n, newPerson);
                displayPersons(arr, n);
                break;
            }
            case 6:
                deleteOldestPerson(arr, &n);
                displayPersons(arr, n);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 7);

    for (int i = 0; i < n; i++) {
        free(arr[i].name);
    }
    free(arr);

    return 0;
}



/*
Define a struct person as follows: 
struct person
{
	int id;
	char *name;
	int age;
	int height;
	int weight;
}; 
Write a menu driven program to read the data of ‘n’ students from a file and store them in a dynamically allocated array of struct person. Implement the min-heap or max-heap and its operations based on the menu options. 

Sample Input/Output:
MAIN MENU (HEAP)
1. Read Data
2. Create a Min-heap based on the age
3. Create a Max-heap based on the weight
4. Display weight of the youngest person
5. Insert a new person into the Min-heap
6. Delete the oldest person
7. Exit

Enter option: 1 
Id	Name			Age   Height	   Weight(pound)
0	Adarsh Hota	            39	77		231
1	Levi Maier		56	77		129
2	Priya Kumari	            63	78		240
3	Dorothy Helton	47	72		229
4	Florence Smith	24	75		171
5	Erica Anyan	            38	73		102
6	Norma Webster	23	75		145

Enter option: 4
Weight of youngest student: 65.77 kg

Note#: Other menu choices are similarly verified.*/