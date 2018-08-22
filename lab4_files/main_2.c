#include <malloc/malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool isLetter(char c) {
    if(c >= 'a' && c <= 'z') return true;
    if(c >= 'A' && c <= 'Z') return true;
    return false;
}
 
bool stringComparison(const char *x, const int sizeX, const char *y, const int sizeY) {
    if(sizeX != sizeY) return false;
    for(int i = 0; i < sizeX; ++i) {
        if(x[i] != y[i]) return false;
    }
    return true;
}
 
void readTextFromFile(int **lenOfWords, char ***listOfWords, int *numberOfWordsInFileN1, FILE *file) {
    char *currWord = (char*)malloc(sizeof(char) * 100);
    char ch = 'q';
    while(true) {
        
        if(ch == EOF) break;
        ch = fgetc(file);
 
        if(isLetter(ch)) {
            int currLen = 0;
            currWord[currLen] = ch;
            while(true) {
                ch = fgetc(file);
                if(isLetter(ch)) {
                    currLen++;
                    currWord[currLen] = ch;
                } else break;
            }
 
            currLen++;
            *numberOfWordsInFileN1 = *numberOfWordsInFileN1 + 1;
 
            *lenOfWords = (int*)realloc(*lenOfWords, *numberOfWordsInFileN1 * sizeof(int));
            (*lenOfWords)[*numberOfWordsInFileN1 - 1] = currLen;
 
            *listOfWords = (char**)realloc(*listOfWords, *numberOfWordsInFileN1 * sizeof(char*));
            (*listOfWords)[*numberOfWordsInFileN1 - 1] = (char*)malloc(sizeof(char) * (currLen + 1));
 
            for(int i = 0; i < currLen; ++i) {
                (*listOfWords)[*numberOfWordsInFileN1 - 1][i] = currWord[i];
            }
        }
    }
 
}
 
void searchForDuplicateWords(int *lenOfWordsInFileN1, char **listOfWordsInFileN1, int numberOfWordsInFileN1,
    int *lenOfWordsInFileN2, char **listOfWordsInFileN2, int numberOfWordsInFileN2) {
    for(int i = 0; i < numberOfWordsInFileN1; ++i) {
        int numberOfRepetitions = 0;
        for(int j = 0; j < numberOfWordsInFileN2; ++j) {
            if(stringComparison(listOfWordsInFileN1[i], lenOfWordsInFileN1[i], listOfWordsInFileN2[j], lenOfWordsInFileN2[j])) {
                numberOfRepetitions++;
            }
        }
        for(int j = 0; j < lenOfWordsInFileN1[i]; ++j) {
            printf("%c", listOfWordsInFileN1[i][j]);
        }
        printf(" in file N2 = %d ", numberOfRepetitions);
        printf("\n");
    }
}
 
void freeMemory(int *lenOfWordsInFileN1, char **listOfWordsInFileN1, int numberOfWordsInFileN1,
    int *lenOfWordsInFileN2, char **listOfWordsInFileN2, int numberOfWordsInFileN2) {
    free(lenOfWordsInFileN1);
    free(lenOfWordsInFileN2);
    for(int i = 0; i < numberOfWordsInFileN1; ++i) {
        free(listOfWordsInFileN1[i]);
    }
    for(int i = 0; i < numberOfWordsInFileN2; ++i) {
        free(listOfWordsInFileN2[i]);
    }
    free(listOfWordsInFileN1);
    free(listOfWordsInFileN2);
}
 
int main() {
 
    int *lenOfWordsInFileN1 = NULL;
    char **listOfWordsInFileN1 = NULL;
    int numberOfWordsInFileN1 = 0;
 
    int *lenOfWordsInFileN2 = NULL;
    char **listOfWordsInFileN2 = NULL;
    int numberOfWordsInFileN2 = 0;
 
    FILE *file1 = fopen("input.txt", "r");
    FILE *file2 = fopen("output.txt", "r");
 
    readTextFromFile(&lenOfWordsInFileN1, &listOfWordsInFileN1, &numberOfWordsInFileN1, file1);
    readTextFromFile(&lenOfWordsInFileN2, &listOfWordsInFileN2, &numberOfWordsInFileN2, file2);
 
    searchForDuplicateWords(lenOfWordsInFileN1, listOfWordsInFileN1, numberOfWordsInFileN1,
        lenOfWordsInFileN2, listOfWordsInFileN2, numberOfWordsInFileN2);
 
    freeMemory(lenOfWordsInFileN1, listOfWordsInFileN1, numberOfWordsInFileN1,
        lenOfWordsInFileN2, listOfWordsInFileN2, numberOfWordsInFileN2);
 
    fclose(file1);
    fclose(file2);
 
    return 0;
}