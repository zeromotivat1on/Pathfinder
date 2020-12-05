#include "../inc/pathfinder.h"

void pathfinder(int diff_amnt, int adj_matrix[diff_amnt][diff_amnt], char **final_islands, int begin_index){
    int min_dist[diff_amnt]; // minimum distance
    int vis_vert[diff_amnt]; // visited vertices
    int temp, minindex, min;
    for (int i = 0; i < diff_amnt; i++){
        min_dist[i] = __INT_MAX__;
        vis_vert[i] = 1;
    }
    min_dist[begin_index] = 0;
    // Dijkstra algorithm
    do {
        minindex = __INT_MAX__;
        min = __INT_MAX__;
        for (int i = 0; i<diff_amnt; i++){ // If the vertice hasn't been bypassed and its weight less than min
            if ((vis_vert[i] == 1) && (min_dist[i] < min)){ // Rewrite variables
                min = min_dist[i];
                minindex = i;
            }
        }
        // Add founded min weight to current vertice's weight
        // and compare it with current min vertice's weight
        if (minindex != __INT_MAX__){
            for (int i = 0; i < diff_amnt; i++){
                if (adj_matrix[minindex][i] > 0){
                temp = min + adj_matrix[minindex][i];
                    if (temp < min_dist[i]){
                        min_dist[i] = temp;
                    }
                }
            }
            vis_vert[minindex] = 0;
        }
    } while (minindex < __INT_MAX__);
    // Path recovering
    for(int i = begin_index; i < diff_amnt; ++i){
        int ver[diff_amnt]; // Array of visited vertices
        int end = i; // Index of last vertice
        int end_index = end;
        if(min_dist[end_index] == 0 || min_dist[end_index] == __INT_MAX__) continue;
        ver[0] = end + 1; // First element - final vertice
        int prev_vert = 1; // Index of previous vertice
        int weight = min_dist[end]; // Weight of last vertice

        while (end != begin_index) { // Untill we reach the first vertice
            for (int i = 0; i < diff_amnt; ++i){ // Check all vertices
                if (adj_matrix[i][end] != 0){ // If there is a connectioon
                    int temp = weight - adj_matrix[i][end]; // Determine the weight of path from previous vertice
                    if (temp == min_dist[i]){ // If the weight coincided with temp that from this vertice a step was executed
                        weight = temp; // Sace new weight
                        end = i;       // Save previous vertice
                        ver[prev_vert] = i + 1; // Write this vertice to array
                        prev_vert++;
                    }
                }
            }
        }
        // Path output 
        mx_printstr("========================================\n");
        mx_printstr("Path: ");
        mx_printstr(final_islands[begin_index]);
        mx_printstr(" -> ");
        mx_printstr(final_islands[end_index]);
        mx_printchar('\n');
        // Rout output (begin vertice at the end of array of prev_vert-elements)
        mx_printstr("Route: ");
        mx_printstr(final_islands[ver[prev_vert - 1] - 1]);
        for (int i = prev_vert - 2; i >= 0; --i){
            mx_printstr(" -> ");
            mx_printstr(final_islands[ver[i] - 1]);
        }
        mx_printchar('\n');
        if(prev_vert == 2){ // If we have only 2 islands
             mx_printstr("Distance: ");
             mx_printint(min_dist[end_index]);
        } 
        else {
            mx_printstr("Distance: ");
            mx_printint(adj_matrix[ver[prev_vert - 1] - 1][ver[prev_vert - 2] - 1]);
            for (int i = prev_vert - 2; i >= 1; --i){
                mx_printstr(" + ");
                mx_printint(adj_matrix[ver[i] - 1][ver[i - 1] - 1]);
            }
            mx_printstr(" = ");
            mx_printint(min_dist[end_index]);
        }
        mx_printstr("\n========================================\n");
    }
}
