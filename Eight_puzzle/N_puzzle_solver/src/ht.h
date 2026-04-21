/* Hash Table */
#ifndef _HT_H_
#define _HT_H_

#include <stddef.h>
#include <stdlib.h>

#define HASH_TABLE_ENTRY_IS_EMPTAY -1 /* All entries in hash table are initialized with this value */

typedef struct {
    int *items; /* Array of indices of the states in explored states array */
    size_t count;
    size_t capacity;
} HashTable;

void hash_table_insert(HashTable *ht, int new_item);
void hash_table_clear(HashTable *ht);
void hash_table_free(HashTable *ht);

#endif // _HT_H_

#ifdef HT_IMPLEMENTATION


#endif // HT_IMPLEMENTATION