#include "pathfinder.h"
#include <stdio.h>


void mx_finder(int ** matrix, const int size, int start, int * distances, int * path) {
    bool visited[size];
    visited[start] = true;

    int helper[size];
    int min_index;
    int w;

    for (int i = 0; i < size; i++) {
        helper[i] = matrix[0][i];
        distances[i] = matrix[start][i];
        path[i] = 0;
    }
    helper[start] = INT_MAX;

    for (int i = 0; i < size; i++) {
        min_index = mx_get_min_index(helper, size);
        w = helper[min_index];
        helper[min_index] = INT_MAX;
        visited[min_index] = true;
        for (int j = 0; j < size; j++) {
            if (visited[j] == false) {
                
                if (distances[j] > w + matrix[min_index][j]) {
                    
                    distances[j] = w + matrix[min_index][j];
                    path[j] = min_index;
                }
            }
        }
        
    }

}


int mx_get_min_index(int * array, int size) {
    int min = INT_MAX;
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (array[i] < min) {
            min = array[i];
            index = i;
        }
    }

    return index;
}
