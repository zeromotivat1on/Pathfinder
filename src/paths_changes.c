#include "../inc/pathfinder.h"

///////////////////////////////////////////////////////////////////////////////////// Need changes
bool pathscmp(pNode *node1, pNode *node2, pNode **result) {
    int node1_tot_dist = 0, node2_tot_dist = 0; 

    pNode *temp_node1 = node1;
    for(int i = 0; temp_node1->parent != NULL; ++i) {
        node1_tot_dist += temp_node1->dist_from_parent;
        temp_node1 = temp_node1->parent;
    }

    pNode *temp_node2 = node2;
    for(int i = 0; temp_node2->parent != NULL; ++i) {
        node2_tot_dist += temp_node2->dist_from_parent;
        temp_node2 = temp_node2->parent;
    }

    temp_node1 = node1;
    char **temp_isl1 = first_last_isl(temp_node1);
    temp_node2 = node2;
    char **temp_isl2 = first_last_isl(temp_node2);

    if((mx_strcmp(temp_isl1[0], temp_isl2[0]) == 0 && mx_strcmp(temp_isl1[1], temp_isl2[1]) == 0)) {
        if(node1_tot_dist > node2_tot_dist) return false;
    }
    else if ((mx_strcmp(temp_isl1[1], temp_isl2[0]) == 0 && mx_strcmp(temp_isl1[0], temp_isl2[1]) == 0)) {
        if(result == NULL) {
            if(node1_tot_dist >= node2_tot_dist) return false;
            return true;
        }
        for(int i = 0; result[i] != NULL; ++i) {
            pNode *temp = result[i];
            if(node1_tot_dist > node2_tot_dist || !pathscmp(node1, temp, NULL)) return false;
        }
    }
    return true;
}

char **first_last_isl(pNode *node){
    char **res = (char **)malloc(sizeof(char *) * 2);
    *(res) = NULL; // Last node
    *(res + 1) = NULL; // First node
    pNode *temp = node;
    *(res) = mx_strdup(node->isl);
    int i = 0;
    while(temp->parent != NULL){
        temp = temp->parent;
        i++;
    }
    *(res + 1) = mx_strdup(temp->isl);
    return res;
}

///////////////////////////////////////////////////////////////////////////////////// Need changes
char **get_isl(pNode *path) {
    int path_size = 0;
    pNode *temp = path;
    for(;temp != NULL; path_size++) temp = temp->parent;

    char **islands = (char **) malloc(sizeof(char *) * (path_size + 1));

    for(int j = 0; j <= path_size; ++j) islands[j] = NULL;

    temp = path;

    for(int j = 0; j < path_size; ++j) {
        islands[j] = mx_strdup(temp->isl);
        temp = temp->parent;
    }

    for (int j = 0; j < path_size / 2; ++j) {
        char *temp = islands[j]; 
        islands[j] = islands[path_size - 1 - j];
        islands[path_size - 1 - j] = temp;
    }

    return islands;
}

///////////////////////////////////////////////////////////////////////////////////// Need changes
void sort_paths(pNode **paths, char **islands) {

    for(int i = 0; paths[i + 1] != NULL; ++i) {

        char **curr_p = first_last_isl(paths[i]); // Current path in arr
        char **next_p = first_last_isl(paths[i + 1]); // Next path in arr

        // If our two paths have the same name at the beginning and at the end
        if(mx_strcmp(curr_p[1], next_p[1]) == 0 
            && mx_strcmp(curr_p[0], next_p[0]) == 0) {

            pNode *temp_curr_p = paths[i];
            char **isl_curr_p = get_isl(temp_curr_p);
            pNode *temp_next_p = paths[i + 1];
            char **isl_next_p = get_isl(temp_next_p);
            int index_curr_p = 0, index_next_p = 0;

            for(int j = 0 ; isl_curr_p[j] != NULL && isl_next_p[j] != NULL; ++j) {
                if(mx_strcmp(isl_curr_p[j], isl_next_p[j]) != 0) {
                    for(int k = 0; islands[k] != NULL; ++k) {
                        if(mx_strcmp(islands[k], isl_curr_p[j]) == 0) break;

                        index_curr_p++;
                    }
                    for(int k = 0; islands[k] != NULL; ++k) {
                        if(mx_strcmp(islands[k], isl_next_p[j]) == 0) break;

                        index_next_p++;
                    }
                    if(index_curr_p != index_next_p) break;
                }
            }
            // Swap paths
            if(index_curr_p > index_next_p) {
                pNode *temp = paths[i];
                paths[i] = paths[i + 1];
                paths[i + 1] = temp;
                i = 0;
            }
        }
    }
}
