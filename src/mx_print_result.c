#include "pathfinder.h"
//#include <stdio.h>

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

                    copy_matrix[i][tmp] = 9998;
                    copy_matrix[tmp][i] = 9998;


                    mx_finder(copy_matrix, size, result);
                    if (once_matrix[i][j] == copy_matrix[i][j]) {
                        mx_print_result(copy_matrix, result, islands, i, j);
                        break;
                    }

                }
            }

        }
    }
}



void mx_print_result(int **matrix, int **result, char **islands, int i, int j) {
    mx_printstr("========================================\n");
    // PATH 
    mx_printstr("Path: ");
    mx_printstr(islands[i]);
    mx_printstr(" -> ");
    mx_printstr(islands[j]);
    mx_printchar('\n');

    //ROUTE 
    mx_printstr("Route: ");
    mx_printstr(islands[i]);


    mx_print_route(result, islands, i, j);
    mx_printchar('\n');
    if (result[i][j] == 0) {
        mx_printstr("Distance: ");
        mx_printint(matrix[i][j]);
        mx_printchar('\n');
    }
    else {
    mx_printstr("Distance: ");
        mx_print_dist(matrix, result, islands, i, j,0);
        mx_printstr(" = ");
        mx_printint(matrix[i][j]);
        mx_printchar('\n');
    }
    mx_printstr("========================================\n");
}


void mx_print_route(int **result, char **islands, int i, int j) {
    if (result[i][j] != 0) {
        mx_print_route(result, islands, i, result[i][j]);
    }
    mx_printstr(" -> ");
    mx_printstr(islands[j]);
}

int mx_print_dist(int **matrix, int **result, char **islands, int i, int j, int sum) {
    if (result[i][j] != 0) {
        sum = matrix[i][ result[i][j]];
        mx_print_dist(matrix, result, islands, i, result[i][j], sum);
    }
    if (matrix[i][j] - sum == 0) {
        mx_printint(sum);
    }
    else {
        mx_printstr(" + ");
        mx_printint(matrix[i][j] - sum);
    }
    return sum;
 }

