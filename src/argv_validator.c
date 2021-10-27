#include "pathfinder.h"

void mx_usage(int argc) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]");
        exit(1);
    }
}

void mx_exist(char const *argv[]) {
    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist");
        close(file);
        exit(1);
    }
    close(file);
}

void mx_empty(char const *argv[]) {
    char *str = mx_file_to_str(argv[1]);
    if (mx_strlen(str) == -1) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty");
        exit(1);
    }
    mx_strdel(&str);
}
