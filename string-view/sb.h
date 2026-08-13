#ifndef _SB_H_
#define _SB_H_

#include <stdio.h>

// [head][array]

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} StringBuilder;

#endif // _SB_H_
