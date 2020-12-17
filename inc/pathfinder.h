#pragma once
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

// Nodes in our list (stores data about current node)
typedef struct p_node{
    int dist_from_parent; // We can represent it like priority
    int full_dist;
    char *isl;
    struct p_node* parent;
}               pNode;

// Prority Queue (for open and closed)
typedef struct p_queue { 
    int priority; // We can represent it like distance from parent to this node
    pNode *n_node;
    struct p_queue* next;   
}              pQueue; 

// Priority Queue (queue.c)
int peek(pQueue** head);
void pop(pQueue** head);
void push(pQueue **head, pNode *n_ptr);
int isEmpty(pQueue** head);

// For A* algorithm (astar.c)
pQueue *new_pqNode(pNode *n_ptr);
pNode *new_nNode(char *isl, int dist_from_parent, int full_dist);
pNode **a_star(int begin, int end, char **islands, int size, int matrix[size][size]);
pNode **generate_successors(pNode *n_node, char **islands, int m_size, int matrix[m_size][m_size]);

// For output (output.c)
void print_output_border();
void print_path(char **first_last_islands);
void print_route(char **islands, int size);
void print_distance(pNode *node, int *distances, int size, int dist_sum);
void output(pNode *node);
void print_res(pNode **res, int size, char **islands);

// For paths modification (path_changes.c)
bool pathscmp(pNode *node1, pNode *node2, pNode **result);
char **first_last_isl(pNode *node);
char **get_isl(pNode *paths);
void sort_paths(pNode **paths, char **islands);

// For parsing file (parse_file.c)
void parse_file(const char *file); // Calls all other functions
bool correct_isl(const char *str);
bool correct_dist(const char *dist);

// Additional functions
int mx_atoi(const char *str); // Converts string to integer
void mx_printerr(const char *s); // Print string in error output

#endif
