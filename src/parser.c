#include "pathfinder.h"
#include <stdio.h>

bool is_contain(char **arr, int size, char *str) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == NULL) {
            return false;
        }
        if (mx_strcmp(arr[i], str) == 0) {
            return true;
        }
    }
    return false;
    
}

int get_strarr_index(char **arr, char *str) {
    for (int i = 0; arr[i] != NULL; i++) {
        //printf("arr = %s        , str = %s\n", arr[i], str);
        if (mx_strcmp(arr[i], str) == 0) {
                return i;
        }
        
    }
    
    return -1;
}


char **parse_islands(char const * filename, int size) {
    char *str = mx_file_to_str(filename);
    char ** first_split = mx_strsplit(str, '-');
    char ** sec_split = mx_strsplit(str, ',');
    char *tmp;


    char **str_arr = malloc(size * sizeof(char *) + 1);
    int j = 0;
    int i = 0;
    int index;
    for (; i < size; i++) {
        index = mx_get_char_index(first_split[i], '\n');
        tmp = (first_split[i] + index + 1);
        if (!is_contain(str_arr, size, tmp)) {
            str_arr[j] = mx_strdup((first_split[i] + index + 1));
            j++;
        }

        index = mx_get_char_index(sec_split[i], '-');
        tmp =  (sec_split[i] + index + 1);
        if (!is_contain(str_arr, size, tmp)) {
            str_arr[j] = mx_strdup((sec_split[i] + index + 1));
            j++;
        }

    }

    //если разкомитить все упадет
    //str_arr[i] = NULL;  

    mx_del_strarr(&first_split);
                
    mx_del_strarr(&sec_split);

    mx_strdel(&str);

    return str_arr;
}


long **parse_to_matrix(const char * filename, char **islands, int size) {

    long **matrix = (long**)malloc(size * sizeof(long*));



    for (int i = 0; i < size; i++) {
        matrix[i] = (long *)malloc(size * sizeof(long));
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = LONG_MAX - INT_MAX;
            }

        }
    }

    char *str = mx_file_to_str(filename);
    char **str_arr = mx_strsplit(str, '\n');
    char tmp[100];
    char digit_tmp[100];
    int iter = 0;
    int digit_iter = 0;
    int x = 0;
    int y = 0;
    int value = 42;
    for (int i = 1; str_arr[i] != NULL; i++) {
        iter = 0;
        for(int j = 0; str_arr[i][j] != '\0'; j++) {
            if (mx_isdigit(str_arr[i][j])) {
                digit_tmp[digit_iter] = str_arr[i][j];
                digit_tmp[digit_iter + 1] = '\0'; 
                digit_iter++;
            }
            if (mx_strlen(digit_tmp) > 0 && !mx_isdigit(str_arr[i][j + 1])) {
                value = mx_atoi(digit_tmp);
                digit_tmp[0] = '\0';
                digit_iter = 0;
            }
            if (mx_is_letter(str_arr[i][j])) {
                tmp[iter] = str_arr[i][j];
                iter++;
            }
            else if(str_arr[i][j] == '-') {
                tmp[iter] = '\0';
                x = get_strarr_index(islands, tmp);
                if (x == -1) {
                    mx_printerr("unexpected error");
                    exit(1);
                }
                else {
                    iter = 0;
                }
            }
            else if (str_arr[i][j] == ',') {
                tmp[iter] = '\0';
                y = get_strarr_index(islands, tmp);
                if (y == -1) {
                    mx_printerr("unexpected error");
                    exit(1);
                }
                else {
                    iter = 0;
                }
            }
        }
        if (matrix[x][y] != LONG_MAX - INT_MAX) {
            mx_printerr("error: duplicate bridges");
            exit(1);
        }
        else {
            matrix[x][y] = value;
            matrix[y][x] = value;
        }

    }
    mx_strdel(&str);
    mx_del_strarr(&str_arr);

    return matrix;
}
