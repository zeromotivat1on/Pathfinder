#include "../inc/libmx.h"

int mx_get_substr_index(char **str, char *sub){
    for(int i = 0; str[i]; ++i)
        if(mx_strcmp(str[i], sub) == 0) return i;
    return -1;
}
