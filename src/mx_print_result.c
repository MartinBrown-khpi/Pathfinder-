#include "pathfinder.h"
#include <stdio.h>

void mx_print_logic(int **matrix,int size, int **result, char **islands) {
    //create once matrix 
    int ** once_matrix = (int**)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        once_matrix[i] = (int *)malloc(size * sizeof(int));
    }
    set_matrix_zero(matrix, once_matrix, size);

    // create copy matrix
    int **copy_matrix = (int**)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        copy_matrix[i] = (int *)malloc(size * sizeof(int));
    }
    set_matrix_zero(matrix, copy_matrix, size);
    
    // create copy result
    int ** once_result = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        once_result[i] = (int *)malloc(size * sizeof(int));
    }
    set_result_zero(once_result, size);


    mx_finder(once_matrix,size, once_result);

    int tmp = 0;
    int deep = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            deep = 0;
            if (i != j) {
                set_matrix_zero(matrix, copy_matrix, size);
                set_result_zero(result, size);
                
                mx_print_result(once_matrix, once_result, islands, i, j);

                tmp = once_result[i][j];
                while (tmp != 0) {
                    tmp = once_result[i][tmp];
                    deep++;
                }
                
                for (int x = deep; x > 0; x--) {
                    
                    
                    tmp = once_result[i][j];
                    for (int y = x; y - 1 > 0; y--) {
                        tmp = once_result[i][tmp];
                    }
                    set_result_zero(result, size);
                    set_matrix_zero(matrix, copy_matrix, size);

                    copy_matrix[i][tmp] = 999;
                    copy_matrix[tmp][i] = 999;


                    mx_finder(copy_matrix, size, result);
                    if (once_matrix[i][j] == copy_matrix[i][j]) {
                        printf("SECOND PRINT\n");
                        mx_print_result(copy_matrix, result, islands, i, j);
                        break;
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

