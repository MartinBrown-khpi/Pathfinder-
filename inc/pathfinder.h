#ifndef PATHFINDER__H
#define PATHFINDER__H
#include "libmx.h"

#define INT_MAX 2147483645
#define MAX_EQUAL_PATH 20

// structures 
typedef struct o_path{
    int *route;
    int *distance;
}   t_path;


//Help func
int mx_atoi(const char *str) ;
int get_first_digit(const char *filename);
int count_lines(const char *filename);
void mx_printerr(const char *err);
bool mx_isdigit(int c);
bool mx_is_letter(char c);
void mx_clear_list(t_list **list);

int get_last_index(int *path, int last);
void set_matrix_zero(int **martix, int size);
void martix_cpy(int **dst, int **src, int size);
void set_walls(int **matrix, int **wall_matrix, int size);

t_path *mx_create_path(int *route, int *distances, int size);
bool is_route_eq(int *fir, int *sec, int j);
bool is_route_in_path_arr(t_path **arr, t_path *path, int sizearr, int j);
void mx_delete_path(t_path *path);
// Validator func 
void mx_usage(int argc);
void mx_exist(char const *argv[]);
void mx_empty(char const *argv[]);
void mx_first_line(char const *argv[]);
void mx_invalid_line(char const *argv[]);
void mx_nuber_of_island(char **file_arr);
void mx_invalid_islands(int first_digit, char **islands);
//Parser func
char **parse_islands(char const * filename, int size);
int **parse_to_matrix(const char * filename, char **islands, int size);
// Finder func
void mx_finder(int ** matrix, const int size, int start, int * distances, int * path);
// Print result func
void mx_print_result(int *distances, int *result, char **islands, int i, int j);
void mx_print_logic(int **matrix,int size, char **islands);
void mx_print_route(int *result, char **islands, int i, int j);
int mx_print_dist(int *distances, int *result, char **islands, int i, int sum);
#endif /* PATHFINDER__H */
