//
//  main.c
//  lab3_num2
//
//  Created by Денис Домашевич on 27.02.2018.
//  Copyright © 2018 Денис Домашевич. All rights reserved.
//

#include <mm_malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int readInt() {
    int res;
    while(true) {
        if(scanf("%d", &res) && getchar() == '\n') {
            return res;
        } else {
            printf("Try again\n");
            while(getchar() != '\n') {}
        }
    }
}

void initialize(int **matrix, int n, int m) {
    for(int i = 0; i < n; ++i) {
        matrix[i] = (int*)malloc(m * sizeof(int));
        for(int j = 0; j < m; ++j) {
            matrix[i][j] = 0;
        }
    }
}

void print3DMatrixMK(int ***matrix, int n, int m, int k) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int p = 0; p < k; ++p) {
                printf("%d", matrix[i][j][p]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void print3DMatrixNM(int ***matrix, int n, int m, int k) {
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int p = 0; p < m; ++p) {
                printf("%d", matrix[j][p][i]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
void print3DMatrixNK(int ***matrix, int n, int m, int k) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int p = 0; p < k; ++p) {
                printf("%d", matrix[j][i][p]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void filling3DMatrix(int ***matrix, int n, int m, int k) {
    for(int i = 0; i < n; ++i) {
        matrix[i] = (int**)malloc(m * sizeof(int*));
        for(int j = 0; j < m; ++j) {
            matrix[i][j] = (int*)malloc(k * sizeof(int));
            for(int p = 0; p < k; ++p) {
                matrix[i][j][p] = rand() % 2;
            }
        }
    }
}

void fillingShadowMatrices(int n, int m, int k, int ***matrix, int **shadowNM, int **shadowNK, int **shadowMK) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int p = 0; p < k; ++p) {
                if(matrix[i][j][p] != 0) {
                    shadowNM[i][j] = 1;
                    shadowNK[i][p] = 1;
                    shadowMK[j][p] = 1;
                }
            }
        }
    }
}

void printAllProjections(int n, int m, int k, int ***matrix, int **shadowNM, int **shadowNK, int **shadowMK) {
    
    printf("\nProjections affecting the NM:\n");
    print3DMatrixNM(matrix, n, m, k);
    
    printf("Projections affecting the NK:\n");
    print3DMatrixNK(matrix, n, m, k);
    
    printf("Projections affecting the MK:\n");
    print3DMatrixMK(matrix, n, m, k);
    
}

void output_matrix(int **matrix, int n, int m) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    
    srand((unsigned int)time(NULL));
    
    printf("Enter n:\n");
    int n = readInt();
    printf("Enter m:\n");
    int m = readInt();
    printf("Enter k:\n");
    int k = readInt();
    
    int ***matrix = (int***)malloc(n * sizeof(int**));
    int **shadowNM = (int**)malloc(n * sizeof(int*));
    int **shadowNK = (int**)malloc(n * sizeof(int*));
    int **shadowMK = (int**)malloc(m * sizeof(int*));
    
    initialize(shadowNM, n, m);
    initialize(shadowNK, n, k);
    initialize(shadowMK, m, k);
    
    filling3DMatrix(matrix, n, m, k);
    printAllProjections(n, m, k, matrix, shadowNM, shadowNK, shadowMK);
    fillingShadowMatrices(n, m, k, matrix, shadowNM, shadowNK, shadowMK);
    
    printf("Matrix shadowNM:\n");
    output_matrix(shadowNM, n, m);
    printf("Matrix shadowNK:\n");
    output_matrix(shadowNK, n, k);
    printf("Matrix shadowMK:\n");
    output_matrix(shadowMK, m, k);
    
    free(shadowNM);
    free(shadowNK);
    free(shadowMK);

    return 0;
}





