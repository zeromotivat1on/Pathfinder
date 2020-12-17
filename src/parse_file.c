#include "../inc/pathfinder.h"

bool correct_isl(const char *isl){
    if(!isl) return false;
    for(int i = 0; i < mx_strlen(isl); ++i){
        if(!mx_isalpha(isl[i])) return false;
    }
    return true;
}

bool correct_dist(const char *dist){
    if(mx_atoi(dist) < 0 || mx_atoi(dist) > __INT_MAX__) return false;
    for(int i = 0; i < mx_strlen(dist); ++i){
        if(!mx_isdigit(dist[i])) return false;
    }
    return true;
}

void parse_file(const char *file){

    char *file_contents = mx_file_to_str(file);
    if(!file_contents){ // If file is empty
        mx_printerr("error: file ");
        mx_printerr(file);
        mx_printerr(" is empty\n");
        exit(0);
    }

    if(file_contents[0] == '\n'){ // Avoiding segmentation fault, if file has more than one new line
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }

    char *isl_amnt = mx_strndup(file_contents, mx_get_char_index(file_contents, '\n')); // First number in file
    for(int i = 0; i < mx_strlen(isl_amnt); ++i){ // Check first number
        if(!correct_dist(mx_del_extra_spaces(&isl_amnt[i]))){
            mx_printerr("error: line 1 is not valid\n");
            exit(0);
        }
    }

    char **bridges_and_distances = mx_strsplit(&file_contents[mx_get_char_index(file_contents, '\n') + 1], '\n'); // The rest file contents (bridges and distances)
    int dec_isl_amnt = mx_atoi(mx_del_extra_spaces(isl_amnt)); // Converted first number in file into integer
    if(dec_isl_amnt < 0 || dec_isl_amnt > __INT_MAX__){ // If the first number exceeds int boundaries
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }

    int line_amnt = 0;
    for(int i = 0; i < mx_strlen(file_contents); ++i){ // Counting lines in file
        if(file_contents[i] == '\n') {
            line_amnt++;
        }
    }

    for(int i = 0; i < line_amnt - 1; ++i){ // Check for correct bridges and distances input
        if(mx_del_extra_spaces(bridges_and_distances[i]) == NULL){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }

    char **bridges = (char **)malloc(line_amnt * 2 * 9);
    char **first_isl = (char **)malloc(line_amnt * 9);
    char **second_isl = (char **)malloc(line_amnt * 9);
    char **islands = (char **)malloc(line_amnt * 2 * 9 + 1); // All islands written to the array line by line
    int temp = 0;

    int sum_of_distances = 0; // For error handling concerned with sum of distances
    char **distances = (char **)malloc(line_amnt - 1);

    for(int i = 0; i < line_amnt - 1; ++i){
        bridges[i] = mx_strndup(bridges_and_distances[i], mx_get_char_index(bridges_and_distances[i], ','));
        first_isl[i] = mx_strndup(bridges[i], mx_get_char_index(bridges[i], '-'));
        second_isl[i] = mx_strndup(&bridges[i][mx_get_char_index(bridges[i], '-') + 1], '-');
        islands[temp] = mx_strndup(bridges[i], mx_get_char_index(bridges[i], '-'));
        temp++;
        islands[temp] = mx_strndup(&bridges[i][mx_get_char_index(bridges[i], '-') + 1], '-');
        temp++;

        distances[i] = mx_strndup(&bridges_and_distances[i][mx_get_char_index(bridges_and_distances[i], ',') + 1], ',');
        sum_of_distances += mx_atoi(distances[i]);

        if(!correct_isl(islands[i]) || !correct_isl(first_isl[i]) || !correct_isl(second_isl[i])){ // If incorrect island input
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            exit(0);
        }
        
        if(!correct_dist(distances[i]) || distances[i] == NULL){ // If incorrect distance input
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }

    int diff_amnt = 0;
    char **final_islands = (char **)malloc((line_amnt - 1) * 2 * 9); // Islands without duplicates
    for(int i = 0; i < (line_amnt - 1) * 2; ++i){ // Write each island only once
        if(mx_get_substr_index(final_islands, islands[i]) == -1) {
            final_islands[diff_amnt] = islands[i];
            diff_amnt++; 
        }
    }

    int adj_matrix[diff_amnt][diff_amnt]; // Adjacency matrix for Dijkstra Algorithm
    for(int i = 0; i < diff_amnt; ++i) // Fill matrixceswith 0's
        for(int j = 0; j < diff_amnt; ++j){
            adj_matrix[i][j] = 0;
        }

    for(int i = 0; i < line_amnt - 1; ++i) { // Filling the adjacency matrix
        distances[i] = mx_strndup(&bridges_and_distances[i][mx_get_char_index(bridges_and_distances[i], ',') + 1], ',');
        adj_matrix[mx_get_substr_index(final_islands, second_isl[i])][mx_get_substr_index(final_islands, first_isl[i])] = mx_atoi(distances[i]);
        adj_matrix[mx_get_substr_index(final_islands, first_isl[i])][mx_get_substr_index(final_islands, second_isl[i])] = mx_atoi(distances[i]);
    }

    if(dec_isl_amnt != diff_amnt){ // If invalid number of islands
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }

    for(int i = 0; i < line_amnt - 1; ++i){ // Check for duplicate bridges
        for(int j = 1; j < line_amnt - 1; ++j){
            if(i != j){
                if(mx_strcmp(bridges[i], bridges[j]) == 0){
                    mx_printerr("error: duplicate bridges\n");
                    exit(0);
                }
            }
        }
    }

    for(int i = 0; i < line_amnt - 1; ++i){ // Check for corrrect sum of bridges
        if(sum_of_distances < 0 || sum_of_distances > __INT_MAX__ || mx_strlen(distances[i]) > 10){
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(0);
        }
    }

    // Part concerned wth A*

    int paths_amnt = 0;
    for(int i = 0; i < diff_amnt; ++i){ // Calculating correct amount of all possible paths (for correct memory allocation)
        for(int j = 0; j < diff_amnt; ++j){
            if(i != j){

                pNode **temp_paths = a_star(i, j, final_islands, diff_amnt, adj_matrix);

                for(int k = 0; temp_paths[k] != NULL; ++k){
                    paths_amnt++;
                }
            }
        }
    }

    int x = 0;
    pNode **paths = (pNode **)malloc(sizeof(pNode *) * (paths_amnt + 1));
    for(int i = 0; i < paths_amnt; ++i){ // Creating and intializing array of pointers 
        paths[i] = (pNode *)malloc(sizeof(pNode));
        paths[i] = NULL;
    }

    for(int i = 0; i < diff_amnt; ++i){
        for(int j = 0; j < diff_amnt; ++j){
            if(i != j){

                pNode **temp_paths = a_star(i, j, final_islands, diff_amnt, adj_matrix);

                for(int k = 0; temp_paths[k] != NULL; ++k){ // Filling our array of pointers
                    paths[x] = temp_paths[k];
                    x++; // x = paths_amnt
                }
            }
        }
    }

    print_res(paths, paths_amnt, final_islands);
}
