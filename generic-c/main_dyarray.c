#include <stdio.h>
#include "src/da.h"

int main(void)
{
    Da *arr = da_new();
    int int_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int i, item;

    for (i=0; i<sizeof(int_arr)/sizeof(int_arr[0]); ++i) {
        da_push(arr, -1, int_arr[i]);
    }
    da_foreach(i, item, arr) {
        printf("%d: %d\n", i, item);
    }
    printf("size: %d, cap: %d\n", arr->size, arr->capacity);
    i = 5;
    item = da_at(i, arr);
    printf("item at %d is %d\n", i, item);

    for (i=0; i<sizeof(int_arr)/sizeof(int_arr[0]); ++i) {
        item = da_pop(arr, -1);
        printf("Poped: %d\n", item);
    }
    printf("size: %d, cap: %d\n", arr->size, arr->capacity);

    return 0;
}
