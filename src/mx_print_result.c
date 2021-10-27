#include "pathfinder.h"
#include <stdio.h>

void mx_print_result(int **matrix,int size, int **result, char **islands) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i != j) {
                printf("========================================\n");
                printf("Path: %s -> %s \n", islands[i], islands[j]); 
                printf("Route: %s ", islands[i]);
                mx_print_route(result, islands, i, j);
                printf("\n");
                printf("Distance: %d \n", matrix[i][j]);
                //mx_print_dist(matrix, result, islands, i, j, matrix[i][j]);
                printf("\n");
                printf("========================================\n");
            }

        }
        printf("\n");
    }
    result[0][0]++;
    matrix[0][0]++;
}

void mx_print_route(int **result, char **islands, int i, int j) {

    if (result[i][j] != 0) {

        mx_print_route(result, islands, i, result[i][j]);
    }
    printf("-> ");
    printf("%s", islands[j]);
}

// int mx_print_dist(int **matrix, int **result, char **islands, int i, int j, int sum) {
    
// }

