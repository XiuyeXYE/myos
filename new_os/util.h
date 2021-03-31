//
// Created by xiuye on 3/31/21.
//

#ifndef CPPOS_UTIL_H
#define CPPOS_UTIL_H

#define asm_v(v) asm volatile(v)
#define seg(v) __attribute__((section(#v)))
#define packed_it __attribute__((packed))

void *memcpy(char *dst, char *src, int n);

#endif //CPPOS_UTIL_H
