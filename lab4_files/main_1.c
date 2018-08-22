#include <malloc/malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
 
const char Vowels[] = {'a', 'e', 'y', 'u', 'i', 'o'};
 
int max(int x, int y) {
    return x > y ? x : y;
}
 
void viewDiagram(char **matrix, int maxHeight) {
    FILE *file2 = fopen("output.txt", "w");
    for(int i = 0; i < maxHeight; ++i) {
        for(int j = 0; j < 6; ++j) {
            putc(matrix[i][j], file2);
            putc(' ', file2);
        }
        putc('\n', file2);
    }
    for(int i = 0; i < 6; ++i) {
        putc(Vowels[i], file2);
        putc(' ', file2);
    }
    fclose(file2);
}
 
void createDiagram(int *quantity) {
    int maxHeight = -1;
    for(int i = 0; i < 6; ++i) {
        maxHeight = max(maxHeight, quantity[i]);
    }
    char **matrix = (char**)malloc(sizeof(char*) * maxHeight);
    for(int i = 0; i < maxHeight; ++i) {
        matrix[i] = (char*)malloc(sizeof(char) * 6);
        for(int j = 0; j < 6; ++j) {
            matrix[i][j] = ' ';
        }
    }
    for(int i = 0; i < 6; ++i) {
        for(int j = maxHeight - 1; j >= maxHeight - quantity[i]; --j) {
            matrix[j][i] = '*';
        }
    }
    viewDiagram(matrix, maxHeight);

    for(int i = 0; i < maxHeight; ++i) {
        free(matrix[i]);
    }
    free(matrix);

}
 
void readText(int *quantity) {
    FILE *file1 = fopen("input.txt", "r");
    char ch = 'Q';
    while(ch != EOF) {
        ch = fgetc(file1);
        if(ch >= 'A' && ch <= 'Z') {
            ch -= 32;
        }
        for(int i = 0; i < 6; ++i) {
            if(Vowels[i] == ch) {
                quantity[i]++;
            }
        }
    }
    fclose(file1);
}
 
int main ()
{
    int *quantity = (int*)malloc(sizeof(int) * 6);
    for(int i = 0; i < 6; ++i) {
        quantity[i] = 0;
    }

    readText(quantity);
    createDiagram(quantity);
    free(quantity);
 
    return 0;
}