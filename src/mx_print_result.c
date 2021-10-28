#include "pathfinder.h"
#include <stdio.h>

void mx_print_logic(int **matrix,int size, int **result, char **islands) {
    // create copy matrix
    int **copy_matrix = (int**)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        copy_matrix[i] = (int *)malloc(size * sizeof(int));
    }
    set_matrix_zero(matrix, copy_matrix, size);
    // create copy result
    
    int tmp = 0;
    int deep = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            deep = 0;
            if (i != j) {
                set_matrix_zero(matrix, copy_matrix, size);
                set_result_zero(result, size);
                mx_finder(copy_matrix,size, result);
                mx_print_result(copy_matrix, result, islands, i, j);

                tmp = result[i][j];
                while (tmp != 0) {
                    tmp = result[i][tmp];
                    deep++;
                }
                //printf("DEEP = %d\n", deep);
                
                for (int x = deep; x > 0; x--) {
                    
                    
                    tmp = result[i][j];
                    for (int y = x; y - 1 > 0; y--) {
                        tmp = result[i][tmp];
                    }
                    // printf("TMP = %d\n", tmp);
                    // printf("matrix = %d\n", copy_matrix[i][tmp]);
                    // printf("matrix = %d\n", copy_matrix[tmp][i]);
                    set_result_zero(result, size);
                    set_matrix_zero(matrix, copy_matrix, size);
                    //PRINT MATRIX
                    copy_matrix[i][tmp] = 999;
                    copy_matrix[tmp][i] = 999;
                    // for (int h = 0; h < size; h++) {
                    //     for (int l = 0; l < size; l++) {
                    //         printf("%d\t", copy_matrix[h][l]);
                    //     }
                    //     printf("\n");
                    // }


                    mx_finder(copy_matrix, size, result);
                    if (matrix[i][j] == copy_matrix[i][j]) {
                        mx_print_result(copy_matrix, result, islands, i, j);
                    }

                }
            }

        }
        printf("\n");
    }
}

void mx_print_result(int **matrix, int **result, char **islands, int i, int j) {
    printf("========================================\n");
    printf("Path: %s -> %s \n", islands[i], islands[j]); 
    printf("Route: %s ", islands[i]);
    mx_print_route(result, islands, i, j);
    printf("\n");
    if (result[i][j] == 0) {
        printf("Distance: %d\n", matrix[i][j]);
    }
    else {
    printf("Distance: ");
        mx_print_dist(matrix, result, islands, i, j,0);
        printf(" = %d\n", matrix[i][j]);
    }
    printf("========================================\n");
}


void mx_print_route(int **result, char **islands, int i, int j) {

    if (result[i][j] != 0) {

        mx_print_route(result, islands, i, result[i][j]);
    }
    printf("-> ");
    printf("%s", islands[j]);
}

int mx_print_dist(int **matrix, int **result, char **islands, int i, int j, int sum) {
    if (result[i][j] != 0) {
        sum = matrix[i][ result[i][j]];
        mx_print_dist(matrix, result, islands, i, result[i][j], sum);
    }
    if (matrix[i][j] - sum == 0) {
        printf("%d", sum);
    }
    else {
        printf(" + %d", matrix[i][j] - sum);
    }
    return sum;
 }

