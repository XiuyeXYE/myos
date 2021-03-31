//
// Created by xiuye on 3/31/21.
//
#include "util.h"

void *memcpy(char *dst, char *src, int n) {
    char *p = dst;
    while (n--)
        *dst++ = *src++;
    return p;
}
