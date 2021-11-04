#include "pathfinder.h"
#include <stdio.h>


void mx_finder(long ** matrix, const int size, int start, long * distances, int * path) {
    bool visited[size];
    

    long min_dist = 0;
    int min_vertex = start;

    for (int i = 0; i < size; i++) {
        distances[i] = matrix[start][i];
        path[i] = -1;
        visited[i] = false;
    }

    int i = 0;
    while (min_dist != LONG_MAX) {
        i = min_vertex;
        visited[min_vertex] = true;
        for (int j = 0; j < size; j++) {
            if (distances[i] + matrix[i][j] < distances[j]) {
                distances[j] = distances[i] + matrix[i][j];
                path[j] = min_vertex;
            }
        }
        min_dist = LONG_MAX;
        for (int j = 0; j < size; j++) {
            if (!visited[j] && distances[j] < min_dist) {
                min_dist = distances[j];
                min_vertex = j;
            }
        }
    }
}

void martix_cpy(long **dst, long **src, int size) {
    if (!dst || !src) {
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

void set_matrix_zero(long **martix, int size) {
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

void set_walls(long **matrix, long **wall_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (wall_matrix[i][j] == LONG_MAX - INT_MAX) {
                matrix[i][j] = LONG_MAX - INT_MAX;
            }
        }
    }
} 

