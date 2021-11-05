#include "pathfinder.h"

void mx_sort_patharr(t_path **arr, int arr_size, int to) {
    t_path *key = NULL;
    int j;
    for (int i = 0; i < arr_size; i++) {
        key = arr[i];
        j = i - 1;


        while (j >= 0 && mx_path_cmp(arr[j], key, to)) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


// Возвращает 1 если первый элемент больше второго
bool mx_path_cmp(t_path *first, t_path *sec, int to) {
    // get min deep
    int first_deep = get_path_deep(first->route, to);
    int sec_deep = get_path_deep(sec->route, to);
    int first_index = to;
    int sec_index = to;
    while (first_deep > 0 && sec_deep > 0) {
        first_index = to;
        sec_index = to;
        for (int i = 0; i < first_deep; i++) {
            first_index = first->route[first_index];
        }
        first_deep--;
        for (int i = 0; i < sec_deep; i++) {
            sec_index = sec->route[sec_index];
        }
        sec_deep--;
        if (first_index > sec_index) {
            return true;
        }
        if (first_index < sec_index) {
            return false;
        }

    }
    if (first_deep > sec_deep) {
        first_index = to;
        for (int i = 0; i < first_deep; i++) {
            first_index = first->route[first_index];
        }
        if (first_index > sec_index) {
            return true;
        }
        return true;
    }
    else if (first_deep < sec_deep) {
        sec_index = to;
        for (int i = 0; i < sec_deep; i++) {
            sec_index = first->route[sec_index];
        }
        if (first_index < sec_index) {
            return false;
        }
        return true;
    }
    else return false;
}

int get_path_deep(int *path, int to) {
    if (path[to] == -1) {
        return 0;
    }
    int deep = 0;
    while (path[to] != -1) {
        to = path[to];
        deep++;
    }
    return deep;
}
