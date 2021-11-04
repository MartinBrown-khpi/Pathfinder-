#include "pathfinder.h"
#include <stdio.h>


void mx_finder(int ** matrix, const int size, int start, int * distances, int * path) {
    bool visited[size];
    

    int min_dist = 0;
    int min_vertex = start;

    for (int i = 0; i < size; i++) {
        distances[i] = matrix[start][i];
        path[i] = -1;
        visited[i] = false;
    }

    int i = 0;
    while (min_dist != INT_MAX) {
        i = min_vertex;
        visited[min_vertex] = true;
        for (int j = 0; j < size; j++) {
            if (distances[i] + matrix[i][j] < distances[j]) {
                distances[j] = distances[i] + matrix[i][j];
                path[j] = min_vertex;
            }
        }
        min_dist = INT_MAX;
        for (int j = 0; j < size; j++) {
            if (!visited[j] && distances[j] < min_dist) {
                min_dist = distances[j];
                min_vertex = j;
            }
        }
    }
}

void martix_cpy(int **dst, int **src, int size) {
    if (!dst || !src) {
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

void set_matrix_zero(int **martix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            martix[i][j] = 0;
        }
    }
}


int get_last_index(int *path, int last) {
    if (!path) {
        return -1;
    }

    while (path[last] != -1) {
        last = path[last];
    }
    return last;
}

void set_walls(int **matrix, int **wall_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (wall_matrix[i][j] == 9999) {
                matrix[i][j] = 9999;
            }
        }
    }
} 

