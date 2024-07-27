/*
2.2 Aim of the program: Write a program in C to find GCD of two numbers using recursion. Read all pair of numbers from a file and store the result in a separate file.

Note# Source file name and destination file name taken from command line arguments. The source file must contain at least 20 pairs of numbers.

Give the contents of the input disc file “inGcd.dat” as  8  12  20  45  30  80

Contents of the output disc file “outGcd.dat” as
The GCD of 8 and 12 is 4
The GCD of 20 and 45 is 5
The GCD of 30 and 80 is 10

Terminal Input:
$gcc lab2q2.c -o lab2q2
$./lab2q2 inGcd.dat outGcd.dat

Output: Display the gcd stored in the output file outGcd.dat
*/

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *sourceFile = argv[1];
    char *destinationFile = argv[2];

    FILE *srcFile = fopen(sourceFile, "r");
    if (!srcFile)
    {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    FILE *destFile = fopen(destinationFile, "w");
    if (!destFile)
    {
        perror("Error opening destination file");
        fclose(srcFile);
        return EXIT_FAILURE;
    }

    int num1, num2;
    int count = 0;

    while (fscanf(srcFile, "%d %d", &num1, &num2) == 2)
    {
        if (num1 <= 0 || num2 <= 0)
        {
            fprintf(stderr, "Invalid input: both numbers must be positive.\n");
            fclose(srcFile);
            fclose(destFile);
            return EXIT_FAILURE;
        }

        int result = gcd(num1, num2);
        fprintf(destFile, "GCD of %d and %d is %d\n", num1, num2, result);

        count++;
        if (count >= 20)
            break;
    }

    if (count < 20)
    {
        fprintf(stderr, "Error: The source file must contain at least 20 pairs of numbers.\n");
        fclose(srcFile);
        fclose(destFile);
        return EXIT_FAILURE;
    }

    fclose(srcFile);
    fclose(destFile);

    return EXIT_SUCCESS;
}