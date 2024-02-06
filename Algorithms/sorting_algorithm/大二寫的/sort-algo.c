#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// ============ creating number array ===============
// ==================================================

int *create_random_num_array(int *num_arr, int arr_size, int seed, int range)
{
    if(seed == -1) srand((unsigned int)time(NULL));
    else srand(seed);

    num_arr = malloc(sizeof(int) * arr_size);

    int i;
    for(i=0; i<arr_size; i++){
        num_arr[i] = rand() % range;
    }

    return num_arr;
}

int *copy_num_array(int *from, int *to, int arr_size){
    int i;
    for(i=0; i<arr_size; i++){
        to[i] = from[i];
    }
    return to;
}

int *free_random_num_array(int *num_arr)
{
    free(num_arr);
    return NULL;
}

void display_num_array(int *num_arr, int arr_size){
    int i;
    for(i=0; i<arr_size; i++){
        printf("%d ", num_arr[i]);
    }
    printf("\n");
}


// ================ swap function ===================
// ==================================================
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


// ================ bubble sort =====================
// ==================================================

int *bubble_sort(int *num_arr, int arr_size)
{
    int i, j;
    for(i=0; i<arr_size-1; i++){
        for(j=0; j+1 < arr_size-i; j++){
            if(num_arr[j] > num_arr[j+1]){
                swap(&num_arr[j], &num_arr[j+1]);
            }
        }
    }
    return num_arr;
}


// ================ insertion sort ==================
// ==================================================

int *insertion_sort(int *num_arr, int arr_size)
{
    int i, j, target;

    // insertion sort
    for(i=0; i<arr_size-1; i++){
        target = num_arr[i+1];
        j=i;
        while(j >= 0 && target < num_arr[j]){
            num_arr[j+1] = num_arr[j];
            j--;
        }
        num_arr[j+1] = target;
    }
    return num_arr;
}


// ================ selection sort ==================
// ==================================================

int *selection_sort(int *num_arr, int arr_size)
{
    int i, j, min, min_position;

    for(i=0; i<arr_size-1; i++){
        min = num_arr[i];
        for(j=i+1; j<arr_size; j++){
            if(min > num_arr[j]){
                min = num_arr[j];
                min_position = j;
            }
        }
        if(min != num_arr[i]){
            swap(&num_arr[i], &num_arr[min_position]);
        }
    }
    return num_arr;
}


// ================== merge sort ====================
// ==================================================

int *merge(int *arr_1, int *arr_2, int **temp, int arr_size)
{
    /* conquer the two array into a sorted array */

    int i, j, index;
    // store the number into the temp array with sorted order until one of the array is ended
    for(i=0, j=0, index=0; i < arr_size/2 && j < arr_size - arr_size/2; index++){
        if(arr_1[i] <= arr_2[j]){
            (*temp)[index] = arr_1[i];
            i++;
        }
        else{
            (*temp)[index] = arr_2[j];
            j++;
        }
    }

    // store the rest into the temp array
    while(i < arr_size/2){
        (*temp)[index] = arr_1[i];
        index++;
        i++;
    }
    while(j < arr_size - arr_size/2){
        (*temp)[index] = arr_2[j];
        index++;
        j++;
    }
}

int *merge_sort(int *num_arr, int arr_size)
{
    /*
        divide and conquer, divide the array into small array, until the array's length is 1
        then conquer two length 1's array into a sorted array with length 2 (or maybe 3)
        then conquer two length 2's array into a sorted array with length 4 (or maybe 5)
        and so on
    */

    /* divide the array into [0:mid] and [mid::] */
    int mid = arr_size / 2;
    if(mid == 0) return num_arr;

    // divide
    merge_sort(num_arr, mid);
    merge_sort(&num_arr[mid], arr_size - mid);

    int *temp = malloc(sizeof(int) * arr_size);

    // conquer
    merge(num_arr, &num_arr[mid], &temp, arr_size);

    // copy back to the original array
    int i;
    for(i=0; i<arr_size; i++){
        num_arr[i] = temp[i];
    }

    free(temp);
    return num_arr;
}


// ================== quick sort ====================
// ==================================================

void swap_q(int *arr, int a, int b){
    int temp;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void quick_sort(int *arr, int left_index, int right_index){
    if(left_index >= right_index) return;
    int i=left_index, j=right_index, target=arr[right_index];
    while(i < j){
        while(arr[i]<=target && i<j) i++;
        while(arr[j]>=target && i<j) j--;
        if(i<j) swap(&arr[i], &arr[j]);
        // for(int a=0; a<10; a++){
        //     printf("%d ", arr[a]);
        // }
        // printf("\n");
    }
    swap(&arr[i], &arr[right_index]);
    // for(int a=0; a<10; a++){
    //     printf("%d ", arr[a]);
    // }
    // printf("\n");

    quick_sort(arr, left_index, i-1);
    quick_sort(arr, i+1, right_index);
}









#if(0)
int main(){
    int *num_arr;

    printf("The initial array: \n");
    num_arr = create_random_num_array(num_arr, ARRAY_LEN, -1, 100);
    display_num_array(num_arr, ARRAY_LEN);

    printf("After sorting: \n");
    num_arr = bubble_sort(num_arr, ARRAY_LEN);
    display_num_array(num_arr, ARRAY_LEN);

    num_arr = free_random_num_array(num_arr);

    return 0;
}
#endif