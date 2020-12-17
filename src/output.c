#include "../inc/pathfinder.h"

void print_output_border(){
    for(int i = 0; i < 40; ++i) mx_printchar('=');
    mx_printchar('\n');
}

void print_path(char **first_last_islands){
    print_output_border();
    
    mx_printstr("Path: ");
    mx_printstr(first_last_islands[1]);
    mx_printstr(" -> ");
    
    mx_printstr(first_last_islands[0]);
    mx_printchar('\n');
}

void print_route(char **islands, int size){
    mx_printstr("Route: ");

    for (int i = size - 1; i >= 0; --i){
        mx_printstr(islands[i]);
        if(i >= 1) mx_printstr(" -> "); // For correct output (avoiding e.g. "a -> b -> ")
    }
    mx_printchar('\n');
}

void print_distance(pNode *node, int *distances, int size, int dist_sum){
    mx_printstr("Distance: ");
   
        if(size == 2){ // If there are only 2 islands, print last min distance from array
            for (int i = size - 2; i >= 0; --i){
                mx_printint(node->dist_from_parent);
                mx_printchar('\n');
                break;
            }
        }
        else{
            for (int i = size - 2; i >= 0; --i){
                mx_printint(distances[i]);
                if(i >= 1) mx_printstr(" + ");
            }
            mx_printstr(" = ");
            mx_printint(dist_sum);
            mx_printchar('\n');
        }
    print_output_border();
}

void output(pNode *node){    
    char **first_last_islands = first_last_isl(node); // Array of first and last island in current path
    print_path(first_last_islands);
    
    int size = 0;
    pNode *temp = node;
    for(; temp != NULL; ++size) temp = temp->parent;

    temp = node;

    char **islands = (char **)malloc(sizeof(char *) * size);
    for(int i = 0; temp != NULL; ++i){ // Filling array with islands
        islands[i] = mx_strdup(temp->isl);
        temp = temp->parent;
    }

    print_route(islands, size);

    temp = node;

    int *distances = (int *)malloc(sizeof(int) * size);
    for(int i = 0; temp != NULL; ++i){
        distances[i] = temp->dist_from_parent; // Filling array with distances
        temp = temp->parent;
    }

    int dist_sum = 0;
    for(int i = 0; i < size - 1; ++i) dist_sum += distances[i];

    print_distance(node, distances, size, dist_sum);
}

///////////////////////////////////////////////////////////////////////////////////// Need changes
void print_res(pNode **paths, int size, char **islands) {

    pNode **result  = (pNode **) malloc(size * sizeof(pNode *));
    for(int i = 0; i < size; ++i) {
        result[i] = NULL;
    }

    int result_size = 0;
    bool insert = true;

    for(int i = 0; paths[i] != NULL; ++i) { // Inserting correct paths to our result (e.g with the same total distance)
        for(int j = 0; paths[j] != NULL; ++j) {
            pNode *temp_i = paths[i]; 
            pNode *temp_j = paths[j];
            if(i != j) {
                if(!pathscmp(temp_i, temp_j, result)) {
                    insert = false;
                    break;
                }
            }
        }
        if (insert == true) {
            result[result_size] = paths[i];
            result_size++;
        }
        insert = true;
    }

    sort_paths(result, islands); // Sorting paths (thx to Oracle <3)

    for(int i = 0; result[i] != NULL; ++i) {
        output(result[i]);
    }
}
