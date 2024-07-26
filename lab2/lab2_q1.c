#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINARY_SIZE 17

void decimalToBinary(int num, char *binaryStr, int index){
    if(num == 0){
        if(index == 0){
            binaryStr[index] = '0';
            binaryStr[index + 1] = '\0';
        }
        return;
    }

    decimalToBinary(num / 2, binaryStr, index - 1);
    binaryStr[index] = (num % 2) ? '1' : '0';
}

void convertToBinary(int num, char *binaryStr){
    memset(binaryStr, '0', MAX_BINARY_SIZE - 1);
    binaryStr[MAX_BINARY_SIZE - 1] = '\0';

    decimalToBinary(num, binaryStr, MAX_BINARY_SIZE - 2);
}

int main(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "Usage: %s <n> <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    char *sourceFile = argv[2];
    char *destinationFile = argv[3];

    FILE *srcFile = fopen(sourceFile, "r");
    if(!srcFile){
        fprintf(stderr, "Error opening source file %s\n", sourceFile);
        return EXIT_FAILURE;
    }

    FILE *destFile = fopen(destinationFile, "w");
    if(!destFile){
        fprintf(stderr, "Error opening destination file %s\n", destinationFile);
        fclose(srcFile);
        return EXIT_FAILURE;
    }

    int num = 0;
    int count = 0;
    char binaryStr[MAX_BINARY_SIZE];

    while(fscanf(srcFile, "%d", &num) == 1 && count < n){
        convertToBinary(num, binaryStr);
        fprintf(destFile, "The binary equivalent of %d is %s\n", num, binaryStr);
        count++;
    }

    fclose(srcFile);
    fclose(destFile);

    destFile = fopen(destinationFile, "r");
    if(!destFile){
        fprintf(stderr, "Error reopening destination file %s\n", destinationFile);
        return EXIT_FAILURE;
    }

    char line[256];
    while (fgets(line, sizeof(line), destFile)){
        printf("%s", line);
    }

    fclose(destFile);

    return EXIT_SUCCESS;
}

