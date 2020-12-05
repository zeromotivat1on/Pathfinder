#include "../inc/pathfinder.h"

int mx_atoi(const char *str) {
    int res = 0, minus = 0;
    for (int i = 0; str[i]; ++i) {
        for (int j = 48; j <= 57; ++j) {
            if((int)str[i] == 45) {
                minus = 1;
                continue;
            }
            if(mx_isspace(str[i])) continue;
            if(!mx_isdigit(str[i])) {
                if(minus == 1) res *= -1;
                return (res / 10);
            }
            if((int)str[i] == j) {
                res += (j - 48);
                if(str[i + 1]) res *= 10;
            }
        }
    }
    if(minus == 1) res *= -1;
    return res;
}
