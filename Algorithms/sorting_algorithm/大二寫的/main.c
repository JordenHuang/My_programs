#include <stdio.h>

#include "sort-algo.c"

#define SIZE 11


int main(){
    int *num_arr;
    int temp[SIZE];

    printf("The initial array: \n");
    num_arr = create_random_num_array(num_arr, SIZE, -1, 100);
    copy_num_array(num_arr, temp, SIZE);
    display_num_array(num_arr, SIZE);

    printf("\nAfter sorting: \n");
    printf("Bubble sort: \n");
    display_num_array(bubble_sort(num_arr, SIZE), SIZE);

    printf("Insertion sort: \n");
    copy_num_array(temp, num_arr, SIZE);
    display_num_array(insertion_sort(num_arr, SIZE), SIZE);

    printf("Selection sort: \n");
    copy_num_array(temp, num_arr, SIZE);
    display_num_array(selection_sort(num_arr, SIZE), SIZE);

    printf("Merge sort: \n");
    copy_num_array(temp, num_arr, SIZE);
    display_num_array(merge_sort(num_arr, SIZE), SIZE);

    printf("Quick sort: \n");
    copy_num_array(temp, num_arr, SIZE);
    quick_sort(num_arr, 0, SIZE-1);
    display_num_array(num_arr, SIZE);


    num_arr = free_random_num_array(num_arr);

    return 0;
}