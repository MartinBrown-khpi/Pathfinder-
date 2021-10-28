#include "pathfinder.h"
#include  <stdio.h>
int main(int argc, char const *argv[])
{
    mx_usage(argc);
    mx_exist(argv);
    mx_empty(argv);
    mx_first_line(argv);
    mx_invalid_line(argv);
    
    
    int count_line = count_lines(argv[1]) - 1;

    int first_digit = get_first_digit(argv[1]);

    char **islands = parse_islands(argv[1], count_line);
                
    mx_invalid_islands(first_digit, islands);

    for (int i = 0; islands[i] != NULL; i++) {
        printf("%d = %s\n", i ,islands[i]);
    }

    int ** matrix = parse_to_matrix(argv[1], islands, first_digit);
    printf("lines = %d\n", count_line);

    for (int i = 0; i < first_digit; i++) {
        for (int j = 0; j < first_digit; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    int **result = (int**)malloc(first_digit * sizeof(int*));
    for (int i = 0; i < first_digit; i++) {
        result[i] = (int *)malloc(first_digit * sizeof(int));
        for (int j = 0; j < first_digit; j++) {
            result[i][j] = 0;
        }
    }
    
    
    mx_print_logic(matrix, first_digit, result, islands);
    
    // FREE MEMORY
    //mx_del_strarr(&islands);
    for(int i = 0; i < first_digit; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
