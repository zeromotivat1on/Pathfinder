#include "../inc/pathfinder.h"

bool correct_isl(const char *isl){
    for(int i = 0; i < mx_strlen(isl); ++i){
        if(!mx_isalpha(isl[i])) return false;
    }
    return true;
}
