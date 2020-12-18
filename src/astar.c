#include "../inc/pathfinder.h"

pQueue *new_pqNode(pNode *node) { 
    pQueue *temp = (pQueue*)malloc(sizeof(pQueue)); 
    temp->priority = node->dist_from_parent; 
    temp->n_node = node;
    temp->next = NULL; 
    return temp; 
} 

pNode *new_nNode(char *isl, int dist_from_parent, int full_dist) { 
    pNode *temp = (pNode*)malloc(sizeof(pNode)); 
    temp->isl = mx_strdup(isl);
    temp->dist_from_parent = dist_from_parent;
    temp->full_dist = full_dist;
    temp->parent = NULL;
    return temp; 
} 

pNode **generate_successors(pNode *n_node, char **islands, int m_size, int matrix[m_size][m_size]){ // Generating successors for current node (n_node)
    pNode **successors = (pNode **)malloc(sizeof(pNode *));

    for(int i = 0; i < m_size; ++i) {
        successors[i] = (pNode*)malloc(sizeof(pNode));
        successors[i] = NULL;
    }

    int i = 0, scssr_index = 0;
    for(;mx_strcmp(islands[i], n_node->isl) != 0; ++i);

    for(int j = 0; j < m_size; ++j){
        if(matrix[i][j] != 0 && i != j) {
            successors[scssr_index] = new_nNode(islands[j], matrix[i][j], n_node->full_dist + matrix[i][j]); 
            scssr_index++;
        }
    }
    return successors;
}

// Find all paths
pNode **a_star(int begin, int end, char **islands, int m_size, int matrix[m_size][m_size]){

    // A* algorithm description

    /* 
     *
     * 1.  Initialize the open list
     * 
     * 2.  Initialize the closed list, put the starting node on the open list
     * 
     * 3.  while the open list is not empty
     * 
     *  a) find the node with the least f on the open list, call it "q"
     * 
     *  b) pop q off the open list
     * 
     *  c) generate q's 8 successors and set their parents to q
     * 
     *  d) for each successor
     * 
     *      i) if successor is the goal, stop search
     *      successor.g = q.g + distance between successor and q
     *      successor.h = distance from goal to successor 
     *      successor.f = successor.g + successor.h
     * 
     *      ii) if a node with the same position as 
     *      successor is in the OPEN list which has a 
     *      lower f than successor, skip this successor
     * 
     *      iii) if a node with the same position as 
     *      successor  is in the CLOSED list which has
     *      a lower f than successor, skip this successor,
     *      otherwise, add  the node to the open list
     * 
     *  end (for loop)
     * 
     *  e) push q on the closed list
     * 
     * end (while loop) 
     * 
     */

    pNode *n_node = new_nNode(islands[begin], 0, 0);
    pQueue *open = new_pqNode(n_node); // Can apply addition and deletion
    pQueue *closed = new_pqNode(n_node); // Only addition, no deletion

    pNode **res = (pNode **)malloc(sizeof(pNode *) * mx_pow(m_size, 2)); // All possible paths from "begin" to "end"

    for(int i = 0; i < m_size; ++i){
        res[i] = (pNode *)malloc(sizeof(pNode));
        res[i] = NULL;
    }

    int res_index = 0;

    while(!isEmpty(&open)){
        n_node = open->n_node; // For route
        pop(&open);

        pNode *temp = n_node;
        
        int a = 0;
        for(; temp->parent != NULL; ++a){
            if(a > m_size) break;
            temp = temp->parent;
        }
        if(a >= m_size) continue;

        bool found_isl = false;
        for(int i = 0; i < m_size; ++i)
            if(mx_strcmp(n_node->isl, islands[i]) == 0) found_isl = true;
        
        if(found_isl == false) continue;

        pNode **successors = generate_successors(n_node, islands, m_size, matrix);

        for(int i = 0; successors[i]; ++i) successors[i]->parent = n_node;

        for(int i = 0; successors[i]; ++i){
            if(mx_strcmp(successors[i]->isl, islands[end]) == 0){
                res[res_index] = successors[i];
                res_index++;
            }

            pQueue *temp_open = open;
            bool in_open = false;;
            while(temp_open != NULL){
                if(mx_strcmp(temp_open->n_node->isl, successors[i]->isl) == 0){
                    if(temp_open->n_node->full_dist < successors[i]->full_dist){
                        in_open = true;
                        break;
                    }
                }
                temp_open = temp_open->next;
            }

            pQueue *temp_closed = closed;
            bool in_closed = false;;
            while(temp_closed != NULL){
                if(mx_strcmp(temp_closed->n_node->isl, successors[i]->isl) == 0){
                    if(temp_closed->n_node->full_dist < successors[i]->full_dist){
                        in_closed = true;
                        break;
                    }
                }
                temp_closed = temp_closed->next;
            }

            if(in_open == false && in_closed == false){
                push(&open, successors[i]);
                push(&closed, successors[i]);
            }
        }
    }
    return res;
}
