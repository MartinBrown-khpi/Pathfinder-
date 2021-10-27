#include "pathfinder.h"

int get_first_digit(const char *filename) {
    char *str = mx_file_to_str(filename);
    int result = mx_atoi(str);
    mx_strdel(&str);
    return result;
} 
