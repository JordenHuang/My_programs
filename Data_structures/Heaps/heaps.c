#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_SIZE 15

typedef struct heap{
    int *arr;  // use array to implement heap
    int capacity;  // the capacity of the heap
    int cur_size;  // to store the current size of the heap, the index of the array
}heap;

/* TODO:
Min heap, Max heap, Min-max heap, Deap

[x]create_heap
[min, max] heapify
[min, max] insertion
[min, max] deletion
[ ]peeking
[x]free heap


From geeksforgeeks:
    A Min heap is typically represented as an array. 

    The root element will be at Arr[0]. 
    For any ith node Arr[i]:
    Arr[(i - 1) / 2] returns its parent node.
    Arr[(2 * i) + 1] returns its left child node.
    Arr[(2 * i) + 2] returns its right child node.

    Insertion: To insert an element into the min heap, we first append the element to the end of the array and then adjust the heap property by repeatedly swapping the element with its parent until it is in the correct position.
    Deletion: To remove the minimum element from the min heap, we first swap the root node with the last element in the array, remove the last element, and then adjust the heap property by repeatedly swapping the element with its smallest child until it is in the correct position.
    Heapify: A heapify operation can be used to create a min heap from an unsorted array.
*/

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

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


// ============ Min Heap (iterative) ================
// ==================================================

void min_heapify(heap *h, int index){
    // bubble down
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int min = index;

    // avoid index error
    if(left >= h->cur_size || left < -1) left = -1;
    if(right >= h->cur_size || right < -1) right = -1;

    // find the smallest element in the index's left or right child
    if(left != -1 && h->arr[left] < h->arr[index]){
        min = left;
    }
    if(right != -1 && h->arr[right] < h->arr[min]){
        min = right;
    }

    // swap the nodes
    if(min != index){
        int temp = h->arr[index];
        h->arr[index] = h->arr[min];
        h->arr[min] = temp;

        // recursively call the heapify function
        min_heapify(h, min);
    }
}

void min_heap_insertion(heap *h, int key){
    /* param:
        *h:
            the head of the heap

        key:
            the priorty, or the data
    */

    // check if the heap still have space to store
    if(h->cur_size + 1 == h->capacity){
        fprintf(stderr, "The heap is full");
        return;
    }

    // insert
    h->arr[++h->cur_size] = key;

    int parent_index = (h->cur_size - 1) / 2, child_index = h->cur_size, temp;
    while(parent_index >= 0){
        if(h->arr[parent_index] > h->arr[child_index]){
            // swap the child and parent
            temp = h->arr[parent_index];
            h->arr[parent_index] = h->arr[child_index];
            h->arr[child_index] = temp;

            // set the next child and parent
            child_index = parent_index;
            parent_index = (child_index - 1) / 2;
        }
        else break;
    };
}

int min_heap_extract_min(heap *h){
    int item = h->arr[0];

    // if the heap is empty
    if(h->cur_size == -1){
        fprintf(stderr, "The min heap is empty"); // not sure this line is correct or not
    }

    // move the last element to the root
    h->arr[0] = h->arr[h->cur_size--];
    // printf("now: %d\n", h->arr[0]);

    // bubble down
    int parent_index = 0;
    int left_index = 1, right_index = 2;  // array index of root's left and right child
    int temp, min = parent_index;

    // check if left or right is in the range
    if(left_index > h->cur_size) left_index = -1;
    if(right_index > h->cur_size) right_index = -1;

    while(left_index != -1 || right_index != -1){
        // compare with the left child first
        if(left_index != -1 && h->arr[left_index] < h->arr[parent_index]){
            min = left_index;
        }
        // then use min to compare with the right child
        if(right_index != -1 && h->arr[right_index] < h->arr[min]){
            min = right_index;
        }

        // swap the parent with the smallest child of the parent
        if(min != parent_index){
            temp = h->arr[parent_index];
            h->arr[parent_index] = h->arr[min];
            h->arr[min] = temp;
        }
        else break;

        // set the next round's left, right and parent
        parent_index = min;
        if(min * 2 + 1 <= h->cur_size){
            left_index = min * 2 + 1;
        }
        else left_index = -1;
        
        if(min * 2 + 2 <= h->cur_size){
            right_index = min * 2 + 2;
        }
        else right_index = -1;
    }

    return item;
}


// ============ Max Heap (recursive) ================
// ==================================================

void max_insertion_helper(heap *h, int index){
    int parent_index = (index - 1) / 2;

    if(parent_index >= 0 && h->arr[parent_index] < h->arr[index]){
        // swap the child and parent
        int temp = h->arr[parent_index];
        h->arr[parent_index] = h->arr[index];
        h->arr[index] = temp;

        // recursive call
        max_insertion_helper(h, parent_index);
    }
}

void max_heap_insertion(heap *h, int key){
    /* param:
        *h:
            the head of the heap

        key:
            the priorty, or the data
    */

    // check if the heap still have space to store
    if(h->cur_size + 1 == h->capacity){
        fprintf(stderr, "The heap is full");
        return;
    }

    // insert
    h->arr[++h->cur_size] = key;

    max_insertion_helper(h, h->cur_size);
}

void max_heapify(heap *h, int index){
    // bubble down
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int max = index;

    // avoid index error
    if(left >= h->cur_size || left < -1) left = -1;
    if(right >= h->cur_size || right < -1) right = -1;

    // find the smallest element in the index's left or right child
    if(left != -1 && h->arr[left] > h->arr[index]){
        max = left;
    }
    if(right != -1 && h->arr[right] > h->arr[max]){
        max = right;
    }

    // swap the nodes
    if(max != index){
        int temp = h->arr[index];
        h->arr[index] = h->arr[max];
        h->arr[max] = temp;

        // recursively call the heapify function
        max_heapify(h, max);
    }
}

int max_heap_extract_max(heap *h){
    int item = h->arr[0];

    // if the heap is empty
    if(h->cur_size == -1){
        fprintf(stderr, "The max heap is empty"); // not sure this line is correct or not
    }

    // move the last element to the root
    h->arr[0] = h->arr[h->cur_size--];
    // printf("now: %d\n", h->arr[0]);

    // bubble down
    max_heapify(h, 0);

    return item;
}



void heap_print_all(heap *h){
    int i;
    for(i=0; i <= h->cur_size; i++){
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}


int main(){
    // HEAP_SIZE is 15
    heap *min_heap = create_heap(HEAP_SIZE);
    heap *max_heap = create_heap(HEAP_SIZE);
    int data[] = {50, 45, 1, 2, 10, 13, 5, 9, 15};
    int i;

    printf("Min heap part: \n");

    for(i=0; i<sizeof(data)/sizeof(int); i++){
        min_heap_insertion(min_heap, data[i]);
    }

    heap_print_all(min_heap);
    /*
        1
        2 9
        13 5 10 15
    */
    

    printf("The smallest element is: %d\n", min_heap_extract_min(min_heap));

    heap_print_all(min_heap);
// 2 5 9 13 15 10


    printf("The smallest element is: %d\n", min_heap_extract_min(min_heap));

    heap_print_all(min_heap);
// 5 10 9 13 15

    printf("The smallest element is: %d\n", min_heap_extract_min(min_heap));

    heap_print_all(min_heap);
// 9 10 15 13


    min_heap = heap_free(min_heap);



    printf("\n-------------\n");
    printf("Max heap part: \n");
    for(i=0; i<sizeof(data)/sizeof(int); i++){
        max_heap_insertion(max_heap, data[i]);
    }

    /*
        15
        10 13
        1 5 2 9
    */

    heap_print_all(max_heap);
// 15 10 13 1 5 2 9
    printf("The largest element is: %d\n", max_heap_extract_max(max_heap));

    heap_print_all(max_heap);
// 13 10 9 1 5 2

    printf("The largest element is: %d\n", max_heap_extract_max(max_heap));

    heap_print_all(max_heap);
// 10 2 9 1 5

    max_heap = heap_free(max_heap);    

    return 0;
}