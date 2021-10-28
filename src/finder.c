#include "pathfinder.h"
#include <stdio.h>
void mx_finder(int **matrix, int size, int **result) {
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    result[i][j] = k;
                }
            }
        }
    }
    // printf("\n\n\n");
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         printf("%d \t", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n\n\n");
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         printf("%d \t", result[i][j]);
    //     }
    //     printf("\n");
    // }
}


void set_result_zero(int **result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
        }
    }
}

void set_matrix_zero(int ** matrix, int ** copy_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            copy_matrix[i][j] = matrix[i][j];
        }
    }    
}
