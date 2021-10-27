#include "pathfinder.h"

void mx_first_line(char const *argv[]) {
    int file = open(argv[1], O_RDONLY);
    char *str = mx_strnew(35);
    mx_read_line(&str, 35, '\n', file);
    if (mx_strlen(str) == 0) {
        mx_printerr("error: line 1 is not valid");
        close(file);
        exit(1);
    }
    for (int i = 0; i < mx_strlen(str); i++) {
        if (!mx_isdigit(str[i])){
            mx_printerr("error: line 1 is not valid");
            mx_strdel(&str);
            close(file);
            exit(1);
        }
    }
    close(file);
    mx_strdel(&str);
}

bool mx_is_letter(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return true;
    }
    return false;
}

void mx_invalid_islands(int first_digit, char **islands) {
    int count_bridges = 0;
    for (;islands[count_bridges] != NULL; count_bridges++);
    if (count_bridges != first_digit) {
        mx_printerr("error: invalid number of islands");
        exit(1);
    }
}


int count_lines(const char *filename) {
    char * str = mx_file_to_str(filename);
    int counter = 0;
    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == '\n') {
            counter++;
        }
    }
    mx_strdel(&str);
    return counter;
}


void mx_invalid_line(char const *argv[]) {
    char *str = mx_file_to_str(argv[1]);
    char **str_arr = mx_strsplit(str, '\n');
    int dash = 0;
    int comma = 0;
    char * to_print;
    //mx_nuber_of_island(str_arr);
    for (int i = 1; str_arr[i] != NULL; i++) {
        dash = mx_get_char_index(str_arr[i], '-');
        comma = mx_get_char_index(str_arr[i], ',');
        if (dash == -1 || comma == -1) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i));
            mx_printerr(" is not valid");
            mx_strdel(&str);
            mx_del_strarr(&str_arr);
            exit(1);
        }

        for (int j = 0; str_arr[i][j] != '\0'; j++) {
            if (!mx_is_letter(str_arr[i][j]) && j != dash && j <= comma && j != comma) {
                mx_printerr("error: line ");
                to_print = mx_itoa(i);
                mx_printerr(to_print);
                mx_printerr(" is not valid");
                mx_strdel(&str);
                mx_strdel(&to_print);
                mx_del_strarr(&str_arr);
                exit(1);
            }
            else if (j > comma && !mx_isdigit(str_arr[i][j])) {
                mx_printerr("error: line ");
                to_print = mx_itoa(i);
                mx_printerr(to_print);
                mx_printerr(" is not valid");
                mx_strdel(&str);
                mx_strdel(&to_print);
                mx_del_strarr(&str_arr);
                exit(1);
            }
        }
        
    }
    mx_strdel(&str);
    mx_del_strarr(&str_arr);
    
}
