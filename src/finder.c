#include "pathfinder.h"
#include <stdio.h>


void mx_finder(int ** matrix, const int size, int start, int * distances, int * path) {
    bool visited[size];
    

    int helper[size];
    int min_dist = 0;
    int min_vertex = start;

    for (int i = 0; i < size; i++) {
        helper[i] = matrix[start][i];
        distances[i] = matrix[start][i];
        path[i] = 0;
        visited[i] = false;
    }
    //visited[start] = true;
    helper[start] = 0;
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
/*
func dijkstra(s):
    for v∈V                    
        d[v] = ∞
        used[v] = false
    d[s] = 0
    for i∈V
        v = null
        for j∈V                        // найдём вершину с минимальным расстоянием
            if !used[j] and (v == null or d[j] < d[v])
                v = j
        if d[v] == ∞
            break
        used[v] = true
        for e : исходящие из v рёбра     // произведём релаксацию по всем рёбрам, исходящим из v
            if d[v] + e.len < d[e.to]
                d[e.to] = d[v] + e.len

*/
