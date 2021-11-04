#include "pathfinder.h"

t_path *mx_create_path(int *route, long *distances, int size) {
    if (!route || !distances) {
        return NULL;
    }

    t_path *new_path = malloc(sizeof(t_path*));
    int *cp_route = (int *)malloc(size * sizeof(int));
    long *cp_dist = (long *)malloc(size * sizeof(long));
    for (int i = 0; i < size; i++) {
        cp_route[i] = route[i];
        cp_dist[i] = distances[i];
    }

    new_path->distance = cp_dist;
    new_path->route = cp_route;
    return new_path;
}

bool is_route_in_path_arr(t_path **arr, t_path *path, int sizearr, int j) {
    for (int i = 0; i < sizearr; i++) {
        if (is_route_eq(arr[i]->route, path->route, j)) {
            return true;
        }
    }
    return false;
}

bool is_route_eq(int *fir, int *sec, int j) {
    int tmp = j;

    while (fir[tmp] == sec[tmp]) {
        if (fir[tmp] == -1 && sec[tmp] == -1) {
        return true;
        }
        tmp = fir[tmp];
    }
    return false;
    
}

void mx_delete_path(t_path *path) {
    if (!path) {
        return;
    }
    free(path->distance);
    free(path->route);
    free(path);
}
