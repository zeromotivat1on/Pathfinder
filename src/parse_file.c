#include "../inc/pathfinder.h"

void parse_file(const char *file){
    char *file_contents = mx_file_to_str(file);
    if(!file_contents){
        mx_printerr("error: file ");
        mx_printerr(file);
        mx_printerr(" is empty\n");
        exit(0);
    }
    if(file_contents[0] == '\n'){
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    char *isl_amnt = mx_strndup(file_contents, mx_get_char_index(file_contents, '\n')); // first number in file
    for(int i = 0; i < mx_strlen(isl_amnt); ++i){
        if(mx_isalpha(isl_amnt[i])){
            mx_printerr("error: line 1 is not valid\n");
            exit(0);
        }
    }
    char **bridges_and_distances = mx_strsplit(&file_contents[mx_get_char_index(file_contents, '\n') + 1], '\n'); // the rest file contents
    int dec_isl_amnt = mx_atoi(isl_amnt); // converted first number in file into integer
    if(dec_isl_amnt < 0 || dec_isl_amnt > __INT_MAX__){
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    int line_amnt = 0;
    for(int i = 0; i < mx_strlen(file_contents); ++i){
        if(file_contents[i] == '\n') {
            line_amnt++;
        }
    }
    for(int i = 0; i < line_amnt - 1; ++i){
        if(bridges_and_distances[i] == NULL){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }
    char **bridges = (char **)malloc(line_amnt * 2 * 9);
    char **first_isl = (char **)malloc(line_amnt * 9);
    char **second_isl = (char **)malloc(line_amnt * 9);
    char **islands = (char **)malloc(line_amnt * 2 * 9 + 1);
    int a = 0;
    for(int i = 0; i < line_amnt - 1; ++i){
        bridges[i] = mx_strndup(bridges_and_distances[i], mx_get_char_index(bridges_and_distances[i], ','));
        first_isl[i] = mx_strndup(bridges[i], mx_get_char_index(bridges[i], '-'));
        second_isl[i] = mx_strndup(&bridges[i][mx_get_char_index(bridges[i], '-') + 1], '-');
        islands[a] = mx_strndup(bridges[i], mx_get_char_index(bridges[i], '-'));
        a++;
        islands[a] = mx_strndup(&bridges[i][mx_get_char_index(bridges[i], '-') + 1], '-');
        a++;
        if(!correct_isl(islands[i]) || !correct_isl(first_isl[i]) || !correct_isl(second_isl[i])){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }
    int diff_amnt = 0;
    char **final_islands = (char **)malloc((line_amnt - 1) * 2 * 9);
    for(int i = 0; i < (line_amnt - 1) * 2; ++i){
        if(mx_get_substr_index(final_islands, islands[i]) == -1) {
            final_islands[diff_amnt] = islands[i];
            diff_amnt++; 
        }
    }
    int adj_matrix[diff_amnt][diff_amnt];
    for(int i = 0; i < diff_amnt; ++i)
        for(int j = 0; j < diff_amnt; ++j)
            adj_matrix[i][j] = 0;
    int sum_of_distances = 0;
    char **distances = (char **)malloc(line_amnt - 1);
    for(int i = 0; i < line_amnt - 1; ++i){
        distances[i] = mx_strndup(&bridges_and_distances[i][mx_get_char_index(bridges_and_distances[i], ',') + 1], ',');
        sum_of_distances += mx_atoi(distances[i]);
        if(!correct_dist(distances[i]) || distances[i] == NULL){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            exit(0);
        }
        adj_matrix[mx_get_substr_index(final_islands, second_isl[i])][mx_get_substr_index(final_islands, first_isl[i])] = mx_atoi(distances[i]);
        adj_matrix[mx_get_substr_index(final_islands, first_isl[i])][mx_get_substr_index(final_islands, second_isl[i])] = mx_atoi(distances[i]);
    }
    if(dec_isl_amnt != diff_amnt){
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
    for(int i = 0; i < line_amnt - 1; ++i){
        for(int j = 1; j < line_amnt - 1; ++j){
            if(i != j){
                if(mx_strcmp(bridges[i], bridges[j]) == 0){
                    mx_printerr("error: duplicate bridges\n");
                    exit(0);
                }
            }
        }
    }
    for(int i = 0; i < line_amnt - 1; ++i){
        if(sum_of_distances < 0 || sum_of_distances > __INT_MAX__ || mx_strlen(distances[i]) > 10){
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(0);
        }
    }
    for(int i = 0; i < diff_amnt; ++i){
        pathfinder(diff_amnt, adj_matrix, final_islands, i); // Implement Dijkstra algorithm and print output
    }
}
