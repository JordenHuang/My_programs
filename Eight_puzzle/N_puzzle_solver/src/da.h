/* Dynamic Array */
#ifndef _DA_H_
#define _DA_H_

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define DA_INITIAL_CAPACITY 256

#define da_new_with_capacity(type, init_capacity)                       \
    (type) {                                                            \
        .items = malloc(sizeof(*(((type *)0)->items)) * init_capacity), \
        .count = 0,                                                     \
        .capacity = init_capacity,                                      \
    }

#define da_append(da, item)                                                          \
    do {                                                                             \
        if ((da)->count >= (da)->capacity) {                                         \
            if ((da)->capacity == 0) {                                               \
                (da)->capacity = DA_INITIAL_CAPACITY;                                \
            } else {                                                                 \
                (da)->capacity *= 2;                                                 \
            }                                                                        \
            (da)->items = realloc((da)->items, sizeof(*(da)->items)*(da)->capacity); \
        }                                                                            \
        (da)->items[(da)->count++] = (item);                                         \
    } while(0)

#define da_pop(da) (da)->items[(assert((da)->count > 0), --(da)->count)]

#define da_free(da) free((da).items)

#define da_first(da) (da)->items[(assert((da)->count > 0), 0)]
#define da_last(da) (da)->items[(assert((da)->count > 0), (da)->count-1)]

#define da_foreach_item(pos, da) for (pos=(da)->items; pos != (da)->items + (da)->count; pos++)

#endif // _DA_H_

#ifdef DA_IMPLEMENTATION
#endif // DA_IMPLEMENTATION