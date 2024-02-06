#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HEAP_SIZE 15

typedef struct heap{
    int *arr;  // use array to implement heap
    int capacity;  // the capacity of the heap
    int cur_size;  // to store the current size of the heap, the index of the array
}heap;


heap *create_heap(int capacity){
    heap *new_heap = (heap *)malloc(sizeof(heap));
    new_heap->arr = (int *)malloc(sizeof(int) * capacity);
    new_heap->capacity = capacity;

    // cur_size is the index of the arr, because it's not stroing any data yet, so set it to -1
    new_heap->cur_size = -1;

    return new_heap;
}

heap *heap_free(heap *h){
    free(h->arr);
    free(h);
    return NULL;
}

void heap_print_all(heap *h){
    int i;
    for(i=0; i <= h->cur_size; i++){
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

// ================== Min Heap ======================
// ==================================================

int find_grand_parent_index(int index)
{
    int parent = (index-1) / 2;
    int grand_parent = (parent-1) / 2;
    if(grand_parent < 0) return -1;
    else return grand_parent;
}

int check_level(int cur_index)
{
    /* 0 for min level, 1 for max level */
    return (int)log2(cur_index+1) + 1;
}

void min_max_heap_min_heapify(heap *h, int index)
{
    int grand_parent = find_grand_parent_index(index);
    if(grand_parent == -1) return;

    // swap if cur is smaller than grandparent
    if(h->arr[index] < h->arr[grand_parent]){
        int temp = h->arr[index];
        h->arr[index] = h->arr[grand_parent];
        h->arr[grand_parent] = temp;
    
        // recursive call the heapify function
        min_max_heap_min_heapify(h, grand_parent);
    }
}

void min_max_heap_max_heapify(heap *h, int index)
{
    int grand_parent = find_grand_parent_index(index);
    if(grand_parent == -1) return;

    // swap if cur is greater than grandparent
    if(h->arr[index] > h->arr[grand_parent]){
        int temp = h->arr[index];
        h->arr[index] = h->arr[grand_parent];
        h->arr[grand_parent] = temp;
    
        // recursive call the heapify function
        min_max_heap_max_heapify(h, grand_parent);
    }
}

void min_max_heap_insertion(heap *h, int key)
{
    // check if the heap still have space to store
    if(h->cur_size + 1 == h->capacity){
        fprintf(stderr, "The heap is full");
        return;
    }

    // insert
    h->arr[++h->cur_size] = key;

    // check insertion level
    int level = check_level(h->cur_size);
    level = level % 2;
    
    // if the new node is at the min level
    if(level == 1){
        int parent = (h->cur_size-1) / 2, temp;
        if(key > h->arr[parent]){
            temp = h->arr[parent];
            h->arr[parent] = h->arr[h->cur_size];
            h->arr[h->cur_size] = temp;

            min_max_heap_max_heapify(h, parent);
        }
        else min_max_heap_min_heapify(h, h->cur_size);
    }
    // or the new node is at the max level
    else if(level == 0){
        int parent = (h->cur_size-1) / 2, temp;
        if(key < h->arr[parent]){
            temp = h->arr[parent];
            h->arr[parent] = h->arr[h->cur_size];
            h->arr[h->cur_size] = temp;

            min_max_heap_min_heapify(h, parent);
        }
        else min_max_heap_max_heapify(h, h->cur_size);
    }
}

int min_max_heap_extract_min(heap *h){
    // if the heap is empty
    if(h->cur_size == -1){
        fprintf(stderr, "The min-max heap is empty"); // not sure this line is correct or not
        return -1;
    }

    // if only have root
    if(h->cur_size == 0){
        return h->arr[h->cur_size--];
    }
    
    int item = h->arr[0];
    
    // move the last element to the root
    int cur_node = 0;
    h->arr[cur_node] = h->arr[h->cur_size--];

    while(1){
        // case 1: if root has no children
        if(cur_node == h->cur_size){
            // FIXME: Weird here
            // h->cur_size--;
            break;
        }
        
        // case 2: if cur node has no grand-children
        else if(check_level(h->cur_size) - check_level(cur_node) < 2){
            // find the smallest in root's child
            int min, left, right;
            left = 2 * cur_node + 1;
            right = 2 * cur_node + 2;
            if(right <= h->cur_size && h->arr[left] > h->arr[right]) min = right;
            else min = left;

            // if cur node is greater than min, then swap
            if(h->arr[min] < h->arr[cur_node]){
                int temp = h->arr[min];
                h->arr[min] = h->arr[cur_node];
                h->arr[cur_node] = temp;
            }
            break;
        }

        // case 3: if the root has grand-children
        else{
            // find the smallest grand-child
            int left_left, left_right, right_left, right_right;
            left_left = 2 * (2*cur_node+1) + 1;
            left_right = 2 * (2*cur_node+1) + 2;
            right_left = 2 * (2*cur_node+2) + 1;
            right_right = 2 * (2*cur_node+2) + 2;
            int min = left_left;
            if(left_right <= h->cur_size && h->arr[min] > h->arr[left_right]) min = left_right;
            if(right_left <= h->cur_size && h->arr[min] > h->arr[right_left]) min = right_left;
            if(right_right <= h->cur_size && h->arr[min] > h->arr[right_right]) min = right_right;

            // if cur node is greater than the min, then swap
            if(h->arr[min] < h->arr[cur_node]){
                int temp = h->arr[min];
                h->arr[min] = h->arr[cur_node];
                h->arr[cur_node] = temp;
            }
            cur_node = min;
        }
    }

    return item;
}

int min_max_heap_extract_max(heap *h){
    // if the heap is empty
    if(h->cur_size == -1){
        fprintf(stderr, "The min-max heap is empty"); // not sure this line is correct or not
        return -1;
    }

    // if only have root
    if(h->cur_size == 0){
        return h->arr[h->cur_size--];
    }
    
    // move the last element to the root
    int cur_node = 1;
    if(h->arr[1] < h->arr[2]) cur_node = 2;
    int item = h->arr[cur_node];
    h->arr[cur_node] = h->arr[h->cur_size--];

    while(1){
        // case 1: if cur node has no children
        if(cur_node == h->cur_size){
            // FIXME: Weird here
            // h->cur_size--;
            break;
        }
        
        // case 2: if cur node has no grand-children
        else if(check_level(h->cur_size) - check_level(cur_node) < 2){
            // find the smallest in cur node's child
            int max, left, right;
            left = 2 * cur_node + 1;
            right = 2 * cur_node + 2;
            if(right <= h->cur_size && h->arr[left] < h->arr[right]) max = right;
            else max = left;

            // if cur node is smaller than max, then swap
            if(h->arr[max] > h->arr[cur_node]){
                int temp = h->arr[max];
                h->arr[max] = h->arr[cur_node];
                h->arr[cur_node] = temp;
            }
            break;
        }

        // case 3: if the cur node has grand-children
        else{
            // find the largest grand-child
            int left_left, left_right, right_left, right_right;
            left_left = 2 * (2*cur_node+1) + 1;
            left_right = 2 * (2*cur_node+1) + 2;
            right_left = 2 * (2*cur_node+2) + 1;
            right_right = 2 * (2*cur_node+2) + 2;
            int max = left_left;
            if(left_right <= h->cur_size && h->arr[max] < h->arr[left_right]) max = left_right;
            if(right_left <= h->cur_size && h->arr[max] < h->arr[right_left]) max = right_left;
            if(right_right <= h->cur_size && h->arr[max] < h->arr[right_right]) max = right_right;

            // if cur node is smaller than the max, then swap
            if(h->arr[max] > h->arr[cur_node]){
                int temp = h->arr[max];
                h->arr[max] = h->arr[cur_node];
                h->arr[cur_node] = temp;
            }
            cur_node = max;
        }
    }

    return item;
}


int main(){
    heap *min_max_heap = create_heap(HEAP_SIZE);
    int data[] = {50, 45, 1, 2, 10, 13, 5, 9, 15};
    int i;


    for(i=0; i<sizeof(data)/sizeof(int); i++){
        min_max_heap_insertion(min_max_heap, data[i]);
        heap_print_all(min_max_heap);
    }

    for(i=0; i<15; i++){
        if(i % 3 == 1)
        min_max_heap_extract_max(min_max_heap);
        else min_max_heap_extract_min(min_max_heap);
        heap_print_all(min_max_heap);
    }


    heap_free(min_max_heap);

    return 0;
}