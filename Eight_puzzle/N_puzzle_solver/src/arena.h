/* Arena Allocator */
#ifndef _ARENA_H_
#define _ARENA_H_

#include <stdio.h>

typedef struct {
    char *begin;
    size_t capacity; /* Number of bytes in the arena */
    size_t size; /* Used size in capacity */
} Arena;

Arena arena_new(size_t bytes);
void arena_destroy(Arena a);
void arena_info(Arena a);

void *arena_alloc(Arena *a, size_t sz);
void arena_reset(Arena *a);

#endif // _ARENA_H_

#ifdef ARENA_IMPLEMENTATION

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

Arena arena_new(size_t bytes)
{
    Arena a;
    a.begin = malloc(bytes);
    a.capacity = bytes;
    a.size = 0;
    return a;
}

void arena_destroy(Arena a)
{
    free(a.begin);
}

void arena_info(Arena a)
{
    printf("Begin       : %p\n", a.begin);
    printf("Capacity    : %zu\n", a.capacity);
    printf("Current size: %zu\n", a.size);
}

void *arena_alloc(Arena *a, size_t sz)
{
    if ((a->size + sz) <= a->capacity) {
        size_t offset = a->size;
        a->size += sz;
        return (void *)(a->begin + offset);
    } else {
        fprintf(stderr, "[ERROR] Not enough capacity for this region\n");
        exit(1);
        return NULL;
    }
}

void arena_reset(Arena *a)
{
    a->size = 0;
}

#endif // ARENA_IMPLEMENTATION