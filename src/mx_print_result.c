#include "pathfinder.h"
//#include <stdio.h>




void mx_print_logic(int **matrix,int size, int **result, char **islands) {
    int * distances = (int *)malloc(size * sizeof(int));
    int *path = (int *)malloc(size * sizeof(int));
    
    

    for (int i = 0; i < size; i++) {
        mx_finder(matrix, size, i, distances, path);
        for (int j = i; j < size; j++) {
        
        if (i != j) {
            mx_print_result(distances, path, islands, i, j);
        }

        }

    }

    result[0][0] = 0;
}



void mx_print_result(int *distances, int *result, char **islands, int i, int j) {
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

    //DISTANCE
    if (result[j] == 0) {
        mx_printstr("Distance: ");
        mx_printint(distances[j]);
        mx_printchar('\n');
    }
    else {
    mx_printstr("Distance: ");
        mx_print_dist(distances, result, islands, j, 0);
        mx_printstr(" = ");
        mx_printint(distances[j]);
        mx_printchar('\n');
    }
    mx_printstr("========================================\n");
}


void mx_print_route(int *result, char **islands, int i, int j) {
    if (result[j] != 0) {
        mx_print_route(result, islands, i, result[j]);
    }
    mx_printstr(" -> ");
    mx_printstr(islands[j]);
}

int mx_print_dist(int *distances, int *result, char **islands, int i, int sum) {
    if (result[i] != 0) {
        sum = distances[result[i]];
        mx_print_dist(distances, result, islands, result[i], sum);
    }
    if (distances[i] - sum == 0) {
        mx_printint(sum);
    }
    else {
        mx_printstr(" + ");
        mx_printint(distances[i] - sum);
    }
    return sum;
 }

