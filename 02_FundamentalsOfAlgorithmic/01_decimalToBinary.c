/*
2.1 Aim of the program: Write a program in C to convert the first ‘n’ decimal numbers of a disc file to binary using recursion. Store the binary value in a separate disc file.

Note# Read the value of ‘n’, source file name and destination file name from command line arguments. Display the decimal numbers and their equivalent binary numbers from the output file.

Give the contents of the input disc file “inDec.dat” as
30  75   2564  …

Contents of the output disc file “outBin.dat” as
The binary equivalent of 30 is 0000000000011110
The binary equivalent of 75 is 0000000001001011
The binary equivalent of 2564 is 0000101000000100

Terminal Input:
$gcc lab2q1.c -o lab2q1
$./lab2q1 150 inDec.dat outBin.dat

Output: Content of the first ‘n’ decimal and their equivalent binary numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINARY_SIZE 17 // including null terminator
#define BINARY_COLUMN_WIDTH 16 // width for binary representation column

void decimalToBinary(int num, char *binaryStr, int index)
{
    if (num == 0)
    {
        if (index == 0)
        {
            binaryStr[index] = '0';
            binaryStr[index + 1] = '\0';
        }
        return;
    }

    decimalToBinary(num / 2, binaryStr, index - 1);
    binaryStr[index] = (num % 2) ? '1' : '0';
}

void convertToBinary(int num, char *binaryStr)
{
    memset(binaryStr, '0', BINARY_COLUMN_WIDTH);
    binaryStr[BINARY_COLUMN_WIDTH] = '\0';

    decimalToBinary(num, binaryStr, BINARY_COLUMN_WIDTH - 1);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <n> <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    char *sourceFile = argv[2];
    char *destinationFile = argv[3];

    FILE *srcFile = fopen(sourceFile, "r");
    if (!srcFile)
    {
        fprintf(stderr, "Error opening source file %s\n", sourceFile);
        return EXIT_FAILURE;
    }

    FILE *destFile = fopen(destinationFile, "w");
    if (!destFile)
    {
        fprintf(stderr, "Error opening destination file %s\n", destinationFile);
        fclose(srcFile);
        return EXIT_FAILURE;
    }

    int num = 0;
    int count = 0;
    char binaryStr[MAX_BINARY_SIZE];

    while (fscanf(srcFile, "%d", &num) == 1 && count < n)
    {
        convertToBinary(num, binaryStr);
        fprintf(destFile, "The binary equivalent of %-4d is %s\n", num, binaryStr);
        count++;
    }

    fclose(srcFile);
    fclose(destFile);

    destFile = fopen(destinationFile, "r");
    if (!destFile)
    {
        fprintf(stderr, "Error reopening destination file %s\n", destinationFile);
        return EXIT_FAILURE;
    }

    char line[256];
    while (fgets(line, sizeof(line), destFile))
    {
        printf("%s", line);
    }

    fclose(destFile);

    return EXIT_SUCCESS;
}
