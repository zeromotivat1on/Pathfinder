#pragma once
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"
#include <stdio.h>
#include <stdlib.h>

void parse_file(const char *file);
int mx_atoi(const char *str);
void mx_printerr(const char *s);
bool correct_isl(const char *str);
bool correct_dist(const char *dist);
int get_index_in_strarr(char **arr, char *sub);
void parse_file(const char *file);
bool correct_dist(const char *dist);
bool correct_isl(const char *isl);
void pathfinder(int diff_amnt, int adj_matrix[diff_amnt][diff_amnt], char **final_islands, int begin_index);

#endif
