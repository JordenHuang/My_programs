#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HEAP_SIZE 95
#define NULL_CHARACTER '|'
#define CODE_MAX_SIZE 80
#define PRINTABLE_ASCII_CHARACTER 95


typedef struct huffman_tree{
    double weight;
    char character;
    struct huffman_tree *left;
    struct huffman_tree *right;
}huffman_tree;

typedef struct huffman_node_heap{
    // huffman_node_heap, priority queue
    
    // an array to store all the huffman node (array of huffman_tree *)
    huffman_tree **data_arr;
    
    // the capacity of the huffman_node_heap
    int capacity;
    
    // to store the current size of the huffman_node_heap, the index of the array
    int cur_size;
}huffman_node_heap;




// ============ Min heap (iterative) ================
// ==================================================

huffman_node_heap *create_min_heap(int capacity){
    huffman_node_heap *new_heap = (huffman_node_heap *)malloc(sizeof(huffman_node_heap));
    new_heap->data_arr = (huffman_tree **)malloc(sizeof(huffman_tree*) * capacity);
    new_heap->capacity = capacity;

    // cur_size is the index of the arr, because it's not stroing any data_arr yet, so set it to -1
    new_heap->cur_size = -1;

    return new_heap;
}

void tree_free_all(huffman_tree **node){
    // traverse in postorder and free the node, the first node passed in is also freed
    if(*node == NULL) return;
    
    tree_free_all(&((*node)->left));
    tree_free_all(&((*node)->right));
    free(*node);
}

huffman_node_heap *heap_free(huffman_node_heap *h){
    // free the huffman tree
    tree_free_all(h->data_arr);

    // free the heap
    free(h->data_arr);
    free(h);
    return NULL;
}


void min_heap_insertion(huffman_node_heap *h, char character, double key, huffman_tree *new_node){
    /* param:
        *h:
            the head of the min heap

        weight:
            the priorty, or the data_arr
        
        character:
            the character with the weight
    */

    // check if the heap still have space to store
    if(h->cur_size == h->capacity){
        fprintf(stderr, "The heap is full");
        return;
    }

    // create a new node and insert
    if(new_node == NULL){
        h->cur_size++;
        huffman_tree *new_node = (huffman_tree *)malloc(sizeof(huffman_tree));
        new_node->weight = key;
        new_node->character = character;
        new_node->left = NULL;
        new_node->right = NULL;
        h->data_arr[h->cur_size] = new_node;
    }

    // or if no need to create a new node, just insert
    else{
        h->cur_size++;
        h->data_arr[h->cur_size] = new_node;
    }

    // bubble up, maintain the heap
    int parent_index = (h->cur_size - 1) / 2;
    int child_index = h->cur_size;
    huffman_tree *temp;
    while(parent_index >= 0){
        if(h->data_arr[parent_index]->weight > h->data_arr[child_index]->weight){
            // swap the child and parent
            temp = h->data_arr[parent_index];
            h->data_arr[parent_index] = h->data_arr[child_index];
            h->data_arr[child_index] = temp;

            // set the next child and parent
            child_index = parent_index;
            parent_index = (child_index - 1) / 2;
        }
        else break;
    };
}

huffman_tree *min_heap_extract_min(huffman_node_heap *h){
    huffman_tree *item = h->data_arr[0];

    // if the huffman_node_heap is empty
    if(h->cur_size == -1){
        fprintf(stderr, "The heap is empty");
    }

    // move the last element to the root
    h->data_arr[0] = h->data_arr[h->cur_size--];

    // bubble down
    int parent_index = 0;
    int left_index = 1, right_index = 2;  // array index of root's left and right child
    int min = parent_index;
    huffman_tree *temp;

    // check if left or right is in the range
    if(left_index > h->cur_size) left_index = -1;
    if(right_index > h->cur_size) right_index = -1;

    while(left_index != -1 || right_index != -1){
        // compare with the left child first
        if(left_index != -1 && h->data_arr[left_index]->weight < h->data_arr[parent_index]->weight){
            min = left_index;
        }
        // then use min to compare with the right child
        if(right_index != -1 && h->data_arr[right_index]->weight < h->data_arr[min]->weight){
            min = right_index;
        }

        // swap the parent with the smallest child of the parent
        if(min != parent_index){
            temp = h->data_arr[parent_index];
            h->data_arr[parent_index] = h->data_arr[min];
            h->data_arr[min] = temp;
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



void heap_print_all(huffman_node_heap *h){
    int i;
    for(i=0; i <= h->cur_size; i++){
        printf("%f %c\n", h->data_arr[i]->weight, h->data_arr[i]->character);
    }
    printf("\n");
}


// ================= Huffman tree ===================
// ==================================================

void inorder(huffman_tree *cur){
    if(cur == NULL) return;
    
    inorder(cur->left);
    printf("%c ", cur->character);

    inorder(cur->right);
}

huffman_tree *create_whole_huffman_tree(huffman_node_heap *h){
    // a is the smallest, b is the second smallest
    huffman_tree *a, *b;

    while(1){
        // if the heap's element count > 1
        if(h->cur_size > 0){
            a = min_heap_extract_min(h);
            b = min_heap_extract_min(h);
        }
        else break;

        // create a and b's parent node and concat them
        huffman_tree *parent = (huffman_tree *)malloc(sizeof(huffman_tree));
        parent->weight = a->weight + b->weight;
        parent->character = NULL_CHARACTER;
        parent->left = a;
        parent->right = b;

        // add the parent to the heap
        min_heap_insertion(h, NULL_CHARACTER, a->weight + b->weight, parent);
        
    }

    // return the root of the huffman tree
    return h->data_arr[0];
}


// ================= path table ===================
// ==================================================

char **create_path_table(int row, int col){
    char **path_table = malloc(sizeof(char *) * row);
    int i;
    for(i=0; i<row; i++){
        path_table[i] = malloc(sizeof(char) * col);
    }

    return path_table;
}

void path_table_free(char ***path_table, int row){
    int i;
    for(i=0; i<row; i++){
        free((*path_table)[i]);
    }
    free(*path_table);
}


void print_path_table(char **table, int row){
    int i;
    for(i=0; i<row; i++){
        printf("%c: %s\n", table[i][0], &table[i][1]);
    }
}

void find_path_recursive(huffman_tree *node, char ***table, char path[], int path_len, int *table_col_index){
    // if node has left, go left
    if(node->left){
        path[path_len] = '0';
        find_path_recursive(node->left, table, path, path_len + 1, table_col_index);
    }

    // if node has right, go right
    if(node->right){
        path[path_len] = '1';
        find_path_recursive(node->right, table, path, path_len + 1, table_col_index);
    }

    // It's a leaf node, so print the character and it's code
    // and write it into the table
    if(node->left == NULL && node->right == NULL){
        printf("%c: ", node->character);
        (*table)[*table_col_index][0] = node->character;
        int i;
        for(i=0; i<path_len; i++){
            printf("%c", path[i]);
            (*table)[*table_col_index][i+1] = path[i];
        }
        (*table)[*table_col_index][i+1] = '\0';
        (*table_col_index)++;
        printf("\n");
    }
}


// ============== encode and decode =================
// ==================================================

void huffman_encode(char **path_table, int path_table_row, char *plain_text, int plain_text_len){
    int i, j;
    for(i=0; i<plain_text_len; i++){
        for(j=0; j<path_table_row; j++){
            if(plain_text[i] == path_table[j][0]){
                printf("%s", &path_table[j][1]);
                break;
            }
            else if(j+1 == path_table_row) printf("%c", NULL_CHARACTER);
        }
    }
}

void huffman_decode(huffman_tree *root, char *binary_string, int binary_string_len){
    int i=0;
    huffman_tree *cur = root;
    while(i < binary_string_len){       // "1110110111111101101111100"
        if(binary_string[i] == '0'){
            cur = cur->left;

            // if it's leaf node
            if(cur->left == NULL && cur->right == NULL){
                printf("%c", cur->character);
                cur = root;
            }
        }
        else if(binary_string[i] == '1'){
            cur = cur->right;
            
            // if it's leaf node
            if(cur->left == NULL && cur->right == NULL){
                printf("%c", cur->character);
                cur = root;
            }
        }
        else{
            printf("%c", NULL_CHARACTER);
        }
        i++;
    }
}


// ============== Frequency counter =================
// ==================================================

typedef struct store{
    char aphabet;
    int count;
}store;

void swap(store *a, store *b){
    store temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(store s[], int size){
    int i, j;

    // bubble sort
    for(i=0; i<size-1; i++){
        for(j=0; j+1 < size-i; j++){
            if(s[j].count > s[j+1].count){
                swap(&s[j], &s[j+1]);
            }
        }
    }
}

void create_weight_file(FILE *text_fp, char *text){
    int i=0, j=0, wall=0, found=0;
    char cur;
    double total_count = 0;
    store s[PRINTABLE_ASCII_CHARACTER] = {'A', 0};
    
    // read text from file
    if(text_fp != NULL){
        // count the frequency of the characters in the file
        while(!feof(text_fp)){
            i = 0;
            cur = fgetc(text_fp);

            if(!isprint(cur)) continue;
            if(cur == ' ') cur = NULL_CHARACTER;
            total_count++;

            for(i=0; i<PRINTABLE_ASCII_CHARACTER; i++){
                if(cur == s[i].aphabet){
                    s[i].aphabet = cur;
                    s[i].count++;
                    break;
                }
                else if(i == wall){
                    i++;
                    s[i].aphabet = cur;
                    s[i].count++;
                    wall++;
                }
            }
        }
        fclose(text_fp);
        
        bubble_sort(s, wall+1);

        // output the frequency to the 'weight.txt'
        FILE *weight_fp = fopen("weight.txt", "w");
        if(weight_fp == NULL){
            printf("Can not open 'weight.txt' to write");
            return;
        }
        for(i=0; i<=wall; i++){
            fprintf(weight_fp, "%c\t%lf\n", s[i].aphabet, (double)s[i].count / total_count);
        }
        fclose(weight_fp);
    }

    // TODO: read from keyboard input
    // else{

    // }
}











// original main function
#if(0)
int main(){
    char character[] = {'A', 'B', 'C', 'D', 'E'};
    double weight[] = {0.19, 0.09, 0.21, 0.12, 0.41};
    char code[] = "1110110111111101101111100";
    
    char ans[8];

    
    int i, j;
    huffman_node_heap *min_heap = create_min_heap(HEAP_SIZE);

    // create the min heap for the characters and it's corresponding weight
    for(i=0; i<sizeof(character)/sizeof(char); i++){
        min_heap_insertion(min_heap, character[i], weight[i], NULL);
    }
    // heap_print_all(min_heap);


    huffman_tree *root = create_whole_huffman_tree(min_heap);
    // inorder(root);


    // decode block
    huffman_tree *cur=root;
    i=0;
    j=0;
    while(i < (sizeof(code)/sizeof(char))){       // "1110110111111101101111100" 
        if(code[i] == '0'){
            if(cur->left == NULL){
                ans[j++] = cur->character;
                cur = root;
                continue;
            }
            cur = cur->left;
        }
        else if(code[i] == '1'){
            if(cur->right == NULL){
                ans[j++] = cur->character;
                cur = root;
                continue;
            }
            cur = cur->right;
        }
        else{
            ans[j++] = cur->character;
            break;
        }
        i++;
    }

    printf("decoded result: ");
    for(i=0; i<8; i++){
        printf("%c", ans[i]);
    }


    // char **encode_table = malloc(sizeof(char *) * 5);
    // for(i=0; i<5; i++){
    //     encode_table[i] = malloc(sizeof(char) * CODE_MAX_SIZE);
    // }
    char **encode_table = create_path_table(5, CODE_MAX_SIZE);
    char path[CODE_MAX_SIZE];
    int table_col_index = 0;
    find_path_recursive(root, &encode_table, path, 0, &table_col_index);
    print_path_table(encode_table, 5);
    
    path_table_free(&encode_table, 5);
    heap_free(min_heap);
    
    return 0;
}
#endif