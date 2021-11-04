#include "pathfinder.h"
//#include <stdio.h>


void print_mx(int **martix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d\t", martix[i][j]);
        }
        printf("\n");
    }
}

void print_arr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n\n");
}

void mx_print_logic(int **matrix,int size, char **islands) {
    int * distances = (int *)malloc(size * sizeof(int));
    int *path = (int *)malloc(size * sizeof(int));
    
    int **default_matrix = (int **)malloc(size * sizeof(int*));
    int **wall_matrix = (int **)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        default_matrix[i] = (int *)malloc(size * sizeof(int));
        wall_matrix[i] = (int *)malloc(size * sizeof(int));
    }
    set_matrix_zero(wall_matrix, size);
    martix_cpy(default_matrix, matrix, size);

    t_path* new_path;
    t_path* path_arr[MAX_EQUAL_PATH];
    int counter = 0;

    for (int i = 0; i < size; i++) {
        
        for (int j = i; j < size; j++) {
            if (i != j) {
                
                // пропуск по дефолным значениям и усановка его как кратчайшего                
                mx_finder(default_matrix, size, i, distances, path);
                path_arr[counter] = mx_create_path(path, distances, size);
                counter++;
                // поиск дополнительных путей, с отсеканием последнего "моста" 
                while (counter < MAX_EQUAL_PATH) {
                                        
                    if (path[j] != -1) {
                        wall_matrix[j][path[j]] = 9999;
                        wall_matrix[path[j]][j] = 9999;
                    }else {
                        wall_matrix[i][j] = 9999;
                        wall_matrix[j][i] = 9999;
                    }

                    set_walls(matrix, wall_matrix, size);
                    mx_finder(matrix, size, i, distances, path);
                    
                    if (distances[j] == path_arr[0]->distance[j]) {
                        path_arr[counter] = mx_create_path(path, distances, size);
                        counter++;
                    } else {
                        break;
                    }
                }

                // установка стен и матрицы в дефолтные
                set_matrix_zero(wall_matrix, size);
                martix_cpy(matrix, default_matrix, size);
                // поиск дополнительных путей, с отсеканием первого "моста" 
                mx_finder(default_matrix, size, i, distances, path);


                while (counter < MAX_EQUAL_PATH) {

                    if (path[j] != -1) {
                        wall_matrix[i][get_last_index(path, path[j])] = 9999;
                        wall_matrix[get_last_index(path, path[j])][i] = 9999;
                    } else {
                        break;
                    }

                    set_walls(matrix, wall_matrix, size);
                    mx_finder(matrix, size, i, distances, path);

                    //print_mx(wall_matrix, size);
                    // printf("\n\n\n\n");

                    if (distances[j] == path_arr[0]->distance[j]) {
                        new_path = mx_create_path(path, distances, size);
                        if (!is_route_in_path_arr(path_arr, new_path, counter, j)) {
                            //printf("new\n");
                            path_arr[counter] = new_path;
                            counter++;
                        }
                        else {
                            mx_delete_path(new_path);
                        }
                        
                    } else {
                        break;
                    }

                }
                
                for (int k = 0; k < counter; k++) {
                    //printf("k = %d\n", k);
                    //print_arr(path_arr[k]->route, size);
                    mx_print_result(path_arr[k]->distance, path_arr[k]->route, islands, i, j);
                    mx_delete_path(path_arr[k]);
                }
                set_matrix_zero(wall_matrix, size);
                martix_cpy(matrix, default_matrix, size);
                counter = 0;
            }
            

        }
        

    }
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
    if (result[j] == -1) {
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
    if (result[j] != -1) {
        mx_print_route(result, islands, i, result[j]);
    }
    mx_printstr(" -> ");
    mx_printstr(islands[j]);
}

int mx_print_dist(int *distances, int *result, char **islands, int i, int sum) {
    if (result[i] != -1) {
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

