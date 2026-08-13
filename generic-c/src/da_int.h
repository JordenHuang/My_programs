/*
 * Dynamic array with type int
 */

#ifndef __DA_H__
#define __DA_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DA_TYPE int
#define DA_LOG(msg) fprintf(stderr, msg"\n");

typedef struct dynamic_array {
    int capacity;
    int size;
    DA_TYPE *items;
} Da;

/**
 * @param index: a int variable
 * @param da: pointer, the array you want loop through
 */
#define da_foreach(index, item, da) \
            for(index=0, item=da->items[index]; index < da->size; item=da->items[++index])

/** Get the item at index
 * Does NOT check the validity of the index
 */
#define da_at(index, da) (da)->items[index]

Da *da_new(void)
{
    Da *arr = (Da*)malloc(sizeof(Da));
    // TODO: make capacity 32
    arr->capacity = 2;
    arr->size = 0;
    arr->items = (DA_TYPE*)malloc(sizeof(DA_TYPE) * arr->capacity);
    return arr;
}

void da_resize(Da *self, int capacity)
{
    if (capacity > self->capacity) {
        self->capacity = capacity;
        DA_TYPE *new_arr = (DA_TYPE*)malloc(sizeof(DA_TYPE) * capacity);
        int i, *temp = self->items;
        for (i=0; i<self->size; ++i) {
            new_arr[i] = self->items[i];
        }
        self->items = new_arr;
        free(temp);
    } else {
        DA_LOG("New capacity must greater than current capacity");
    }
}

int da_size(Da *self)
{
    return self->size;
}

bool da_empty(Da *self)
{
    if (self->size == 0) return true;
    else return false;
}

void da_clear(Da *self)
{
    self->size = 0;
}

/** Push the item to the index of the array, the rest items will move back
 * Index starts from 0
 * If index equals -1, then push to the back of the array (like append)
 */
void da_push(Da *self, int index, DA_TYPE item)
{
    // Check if it needs resize
    if (self->size == self->capacity) da_resize(self, self->capacity * 2);
    // Then insert
    if (index == -1 || self->size == 0) {
        self->items[self->size] = item;
        self->size += 1;
    } else if (index < self->size) {
        int cur = self->size;
        while (cur != index) {
            self->items[cur] = self->items[cur-1];
            --cur;
        }
        self->items[cur] = item;
        self->size += 1;
    } else {
        DA_LOG("Index out of bound");
    }
}

DA_TYPE da_pop(Da *self, DA_TYPE index)
{
    if (da_empty(self)) {
        DA_LOG("The array is empty");
    }
    DA_TYPE poped; 
    if (index == -1) {
        self->size -= 1;
        poped = self->items[self->size];
    } else if (index < self->size) {
        poped = self->items[index];
        int cur = index;
        for (;cur < self->size - 1; ++cur) {
            self->items[cur] = self->items[cur+1];
        }
        self->size -= 1;
    } else {
        DA_LOG("Index out of bound");
        poped = (DA_TYPE)0;
    }
    return poped;
}

#endif  // __DA_H__
