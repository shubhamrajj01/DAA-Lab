#include <stdio.h>
#include <stdlib.h>

// Structure to represent a symbol with its frequency
typedef struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL *left, *right;
} SYMBOL;

// A Min-Heap structure with the size and an array of SYMBOL pointers
typedef struct {
    int size;
    int capacity;
    SYMBOL **array;
} MinHeap;

// Function to create a new SYMBOL node
SYMBOL* newSymbolNode(char alphabet, int frequency) {
    SYMBOL* temp = (SYMBOL*)malloc(sizeof(SYMBOL));
    temp->alphabet = alphabet;
    temp->frequency = frequency;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to create a Min-Heap of given capacity
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (SYMBOL**)malloc(minHeap->capacity * sizeof(SYMBOL*));
    return minHeap;
}

// Function to swap two SYMBOL pointers
void swapSymbol(SYMBOL** a, SYMBOL** b) {
    SYMBOL* temp = *a;
    *a = *b;
    *b = temp;
}

// A standard function to heapify at the given index
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapSymbol(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if the size of the heap is 1
int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Function to extract the minimum value node from the heap
SYMBOL* extractMin(MinHeap* minHeap) {
    SYMBOL* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Function to insert a new node to Min-Heap
void insertMinHeap(MinHeap* minHeap, SYMBOL* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Function to build a Min-Heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Function to create and build a Min-Heap from input characters and frequencies
MinHeap* createAndBuildMinHeap(char alphabets[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newSymbolNode(alphabets[i], frequencies[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function that builds the Huffman Tree
SYMBOL* buildHuffmanTree(char alphabets[], int frequencies[], int size) {
    SYMBOL *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(alphabets, frequencies, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newSymbolNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Function to perform in-order traversal of the Huffman Tree
void inorderTraversal(SYMBOL* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);

    if (root->alphabet != '$')
        printf("%c ", root->alphabet);

    inorderTraversal(root->right);
}

int main() {
    int n;
    
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabets[n];
    int frequencies[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &alphabets[i]);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &frequencies[i]);
    }

    SYMBOL* root = buildHuffmanTree(alphabets, frequencies, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}


/* Aim of the program: Huffman coding assigns variable length code words to fixed length
input characters based on their frequencies or probabilities of occurrence. Given a set of
characters along with their frequency of occurrences, write a c program to construct a Huffman
tree. Note#
● Declare a structure SYMBOL having members alphabet and frequency. Create a Min- Priority Queue, keyed on frequency attributes. ● Create an array of structures where size=number of alphabets. Input:
Enter the number of distinct alphabets: 6
Enter the alphabets: a b c d e f
Enter its frequencies: 45 13 12 16 9 5
Output:
In-order traversal of the tree (Huffman): a c b f e d*/