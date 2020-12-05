#include "../inc/pathfinder.h"

bool correct_dist(const char *dist){
    if(mx_atoi(dist) < 0 || mx_atoi(dist) > __INT_MAX__) return false;
    for(int i = 0; i < mx_strlen(dist); ++i){
        if(!mx_isdigit(dist[i])) return false;
    }
    return true;
}
