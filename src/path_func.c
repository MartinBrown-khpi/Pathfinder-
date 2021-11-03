#include "pathfinder.h"

t_path *mx_create_path(int *route, int *distances, int size) {
    if (!route || !distances) {
        return NULL;
    }

    t_path *new_path = malloc(sizeof(t_path*));
    int *cp_route = (int *)malloc(size * sizeof(int));
    int *cp_dist = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        cp_route[i] = route[i];
        cp_dist[i] = distances[i];
    }

    new_path->distance = cp_dist;
    new_path->route = cp_route;
    return new_path;
}

bool is_in_path_arr(t_path *arr, t_path path, int sizearr, int size_path_arr) {
    for (int i = 0; i < sizearr; i++) {
        for (int j = 0; j < size_path_arr; j++) {
            if (arr[i].distance[j] != path.distance[j]) {
                return false;
            }
            if (arr[i].route[j] != path.route[j]) {
                return false;
            }
        }
    }
    return true;
}

void mx_delete_path(t_path *path) {
    if (!path) {
        return;
    }
    free(path->distance);
    free(path->route);
    free(path);
}
