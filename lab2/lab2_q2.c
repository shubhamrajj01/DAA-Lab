#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *sourceFile = argv[1];
    char *destinationFile = argv[2];

    FILE *srcFile = fopen(sourceFile, "r");
    if (!srcFile) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    FILE *destFile = fopen(destinationFile, "w");
    if (!destFile) {
        perror("Error opening destination file");
        fclose(srcFile);
        return EXIT_FAILURE;
    }

    int num1, num2;
    int count = 0;

    while (fscanf(srcFile, "%d %d", &num1, &num2) == 2) {
        if (num1 <= 0 || num2 <= 0) {
            fprintf(stderr, "Invalid input: both numbers must be positive.\n");
            fclose(srcFile);
            fclose(destFile);
            return EXIT_FAILURE;
        }

        int result = gcd(num1, num2);
        fprintf(destFile, "GCD of %d and %d is %d\n", num1, num2, result);

        count++;
        if (count >= 20) break;
    }

    if (count < 20) {
        fprintf(stderr, "Error: The source file must contain at least 20 pairs of numbers.\n");
        fclose(srcFile);
        fclose(destFile);
        return EXIT_FAILURE;
    }

    fclose(srcFile);
    fclose(destFile);

    return EXIT_SUCCESS;
}

