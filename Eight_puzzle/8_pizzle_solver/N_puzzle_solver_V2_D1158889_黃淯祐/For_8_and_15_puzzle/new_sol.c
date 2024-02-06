#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


#define SIDE_LENGTH 4
// #define PUZZLE_SIZE SIDE_LENGTH*SIDE_LENGTH
#define NEW_NODES_ARR_SIZE 4

enum move_type{up=-2, down, left, right};
enum Bool_type{False, True};

struct node_struct{
    int                  state[SIDE_LENGTH][SIDE_LENGTH];
    int                  hole_pos[2];
    enum move_type       move;
    int                  depth;      // g
    int                  heuristic;  // h
    int                  f;          // f = h + g
};

typedef struct node_struct nodes;
typedef enum Bool_type bool;
typedef enum move_type moves;


//---linked list part----------------------------------------------------------------------------------------//
struct list_node{
    nodes *puzzle_node;
    struct list_node *previous_node;
    struct list_node *next_node;
};

typedef struct list_node list;


list *list_head = NULL;  // global list-----------------------------------------------------------------------------//
list *last_node = NULL;
// list *prev_node = NULL;


void list_append(nodes *puzzle_node){
    
// printf("\nlist 1\n");

    // create a new node of list and assign data into it
    list *new_node = malloc(sizeof(list));
    new_node->puzzle_node = puzzle_node;
    new_node->previous_node = NULL;
    new_node->next_node = NULL;
    

// printf("list 2\n");
    
    if(list_head == NULL){
        list_head = new_node;
        // printf("list 2.1\n");
    }
    else{
        new_node->previous_node = last_node;
        last_node->next_node = new_node;
        // printf("list 2.2\n");
    }

// printf("list 3\n");

    last_node = new_node;

}


void list_pop(){
    // list *pre_node;
    // nodes *poped_node;

    if(list_head->next_node == NULL){
        // printf("list pop 1.1\n");
        // poped_node = list_head->puzzle_node;
        last_node = NULL;
        free(list_head);
        list_head = NULL;
        return;
        // return poped_node;
    }

    // pop the last node and set the previous's next node to NULL

    // pre_node = last_node->previous_node;
    // pre_node->next_node = NULL;
    // poped_node = last_node->puzzle_node;
    // free(last_node);
    // last_node = pre_node;

    last_node = last_node->previous_node;
    free(last_node->next_node);
    last_node->next_node = NULL;

    // return poped_node;
}

bool is_in_list(nodes *node){
    list *cur = list_head;
    int i, j, same=0, to_break=0;

    while(cur != NULL){
        same = 0;
        // hole_pos not the same --> means two state is different, so continue
        if((cur->puzzle_node->hole_pos[0] != node->hole_pos[0]) || (cur->puzzle_node->hole_pos[1] != node->hole_pos[1])){
            cur = cur->next_node;
            continue;
        }
        // (just try) if two state's heuristic is different, then the two state is different
        if(cur->puzzle_node->heuristic != node->heuristic){
            cur = cur->next_node;
            continue;
        }
        for(i=0, to_break=0; i<SIDE_LENGTH && to_break == 0; i++){
            for(j=0; j<SIDE_LENGTH; j++){
                // if(cur->puzzle_node->state[i][j] == node->state[i][j]){
                //     same++;
                // }
                // else{
                //     to_break = 1;
                //     break;
                // }
                if(cur->puzzle_node->state[i][j] != node->state[i][j]){
                    to_break = 1;
                    break;
                }
            }
        }
        // if(same == SIDE_LENGTH*SIDE_LENGTH) return True;
        if(to_break == 0) return True;
        cur = cur->next_node;
    }
    return False;
}




/*
void list_clear(list *list_head){
    list *pre=list_head->next_node;  // the node after list head
    list *current=pre->next_node;  // the second node after list head

    list_head->next_node = NULL;

    while(current != NULL){
        free(pre);
        pre = current;
        current = current->next_node;
    }
    free(pre);
}
*/
//-----------------------------------------------------------------------------------------------------------//






int goal_state[SIDE_LENGTH][SIDE_LENGTH];
int infinite=500000;
int min;
unsigned long long total_nodes=0;
int move_count=0;
bool found_goal_state = False;
nodes *start_state;

FILE *fp;





void swap(nodes* *a, nodes* *b){
    nodes *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(nodes* s[], int size){
    int i, j;

    // bubble sort
    for(i=0; i<size-1; i++){
        for(j=0; (j+1 < size-i) && (s[j+1] != NULL); j++){
            if(s[j]->heuristic > s[j+1]->heuristic){
                swap(&s[j], &s[j+1]);
            }
        }
    }
}






void set_goal_state(){
    int i, j, num=1;
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++, num++){
            if(i==SIDE_LENGTH-1 && j==SIDE_LENGTH-1) num = 0;
            goal_state[i][j] = num;
        }
    }
}



int row_lc(nodes *node, int r){
    int j, k, conf=0;
    
    for(j=0; j<SIDE_LENGTH-1; j++){
        if(node->state[r][j] == 0) continue;
        if((node->state[r][j]-1) / SIDE_LENGTH == r){
            for(k=j+1; k<SIDE_LENGTH; k++){
                if(node->state[r][k] == 0 || ((node->state[r][k]-1) / SIDE_LENGTH != r)) continue;
                // if() continue;
                else if(node->state[r][k] < node->state[r][j]) conf++;
            }
        }
    }
    return conf;
}


int col_lc(nodes *node, int c){
    int i, k, conf=0;
    
    for(i=0; i<SIDE_LENGTH-1; i++){
        if(node->state[i][c] == 0) continue;
        if((node->state[i][c]-1) % SIDE_LENGTH == c){
            for(k=i+1; k<SIDE_LENGTH; k++){
                if(node->state[k][c] == 0 || ((node->state[k][c]-1) % SIDE_LENGTH != c)) continue;
                // if() continue;
                else if(node->state[k][c] < node->state[i][c]) conf++;
            }
        }
    }
    return conf;
}



int linear_confilct(nodes *node){
    int i, j, k;
    int conf=0;

    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH-1; j++){
            if(node->state[i][j] == 0) continue;
            // for rows
            if((node->state[i][j]-1) / SIDE_LENGTH == i){
                for(k=j+1; k<SIDE_LENGTH; k++){
                    if(node->state[i][k] == 0) continue;
                    if((node->state[i][k]-1) / SIDE_LENGTH != i) continue;
                    else if(node->state[i][k] < node->state[i][j]) conf++;
                }
            }
            // for columns
            if((node->state[i][j]-1) % SIDE_LENGTH == j){    
                for(k=i+1; k<SIDE_LENGTH; k++){
                    if(node->state[k][j] == 0) continue;
                    if((node->state[k][j]-1) % SIDE_LENGTH != j) continue;
                    else if(node->state[k][j] < node->state[i][j]) conf++;
                }
            }
        }
    }
    // printf("conf is: %d\n", conf*2);
    return conf;
}



int manhattan_dis(nodes *node, int r, int c){
    return abs(r - ((node->state[r][c] - 1) / SIDE_LENGTH))
            + abs(c - ((node->state[r][c] - 1) % SIDE_LENGTH));
}


int heuristic_calculate(nodes *node){
    int i, j, dis=0;
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            if((node->state[i][j] != goal_state[i][j]) && (node->state[i][j] != 0)){
                dis += manhattan_dis(node, i, j);
            }
        }

        dis += (row_lc(node, i) + col_lc(node, i)) * 2;
    }

    // dis += linear_confilct(node) * 2;
        
    return dis;
}


bool at_goal(nodes *node){
    int i, j;

    for (i = 0; i < SIDE_LENGTH; i++)
        for (j = 0; j < SIDE_LENGTH; j++)
            if ((node->state[i][j]) != goal_state[i][j]){
                return False;
            }

    return True;
}


nodes *get_start_state(){
    int  i, j, n=0;
    char check[8];  // just for store user choise
    nodes *node= malloc(sizeof(nodes));
    // FILE *fp = fopen("size_3.txt", "w");

    // if(fp == NULL){
    //     printf("CANNOT open file to write initial state!");
    //     exit(1);
    // }

    do {
        printf("Enter a VALID situation of a %d puzzle\n", SIDE_LENGTH*SIDE_LENGTH-1);
        printf("Use a zero to present the hole\n");
        printf("Example: ");
        for(i=0; i<SIDE_LENGTH; i++){
            for(j=0; j<SIDE_LENGTH; j++){
                printf(" %2d", goal_state[i][j]);
            }
            printf("\n\t ");
        }
        printf("\n\n");


        for(i=0; i<SIDE_LENGTH; i++){
            for(j=0; j<SIDE_LENGTH; j++){
                scanf("%d", &node->state[i][j]);
            }
        }
        fflush(stdin);

        printf("\nStarting configuration is: \n");
        for (i = 0; i < SIDE_LENGTH; i++){
            printf("     ");
            for (j = 0; j < SIDE_LENGTH; j++) printf(" %2d", node->state[i][j]);
            printf("\n");
        }
        printf("\nIs that correct? (y/n): ");
        gets(check);
    }while((check[0] != 'Y') && (check[0] != 'y'));


    // set the 0 position to the hole_pos field
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            if(node->state[i][j] == 0){
                node->hole_pos[0] = i;
                node->hole_pos[1] = j;
            }
            fprintf(fp, " %2d", node->state[i][j]);
        }
        fprintf(fp, "\n");
    }

    node->depth = 0;
    node->heuristic = heuristic_calculate(node);
    node->f = node->depth + node->heuristic;
    



    return node;
}



void expand_nodes(nodes *new_nodes[]){
    nodes *current_node = last_node->puzzle_node;
    nodes *new_puzzle_node;
    moves move;
    int row_of_0, column_of_0, next_r_of_0, next_c_of_0, prev_r_of_0, prev_c_of_0;
    int i, j, pos=0;

    // set the previous position of 0
    if(last_node->previous_node == NULL){
        prev_r_of_0 = -1;
        prev_c_of_0 = -1;
    }
    else{
        prev_r_of_0 = last_node->previous_node->puzzle_node->hole_pos[0];
        prev_c_of_0 = last_node->previous_node->puzzle_node->hole_pos[1];
    }

    // set the current position of 0
    row_of_0 = current_node->hole_pos[0];
    column_of_0 = current_node->hole_pos[1];


    // trying four moves to find the next puzzle node
    for(move = up; move <= right; move++){
        // printf("expand 3.0\n");
        switch(move){
            case up:
            next_r_of_0 = row_of_0 - 1;
            next_c_of_0 = column_of_0;
            // printf("\nmove is: %d\n", move);
            break;

            case down:
            next_r_of_0 = row_of_0 + 1;
            next_c_of_0 = column_of_0;
            // printf("\nmove is: %d\n", move);
            break;

            case left:
            next_r_of_0 = row_of_0;
            next_c_of_0 = column_of_0 - 1;
            // printf("\nmove is: %d\n", move);
            break;

            case right:
            next_r_of_0 = row_of_0;
            next_c_of_0 = column_of_0 + 1;
            // printf("\nmove is: %d\n", move);
            break;
        }

        

        // check if it's a new next node (means it doesn't repeat the old move)
        if((next_r_of_0 < 0) || (next_r_of_0 >= SIDE_LENGTH) || (next_c_of_0 < 0) || 
           (next_c_of_0 >= SIDE_LENGTH) || ((next_r_of_0 == prev_r_of_0) && (next_c_of_0 == prev_c_of_0))){
            // printf("Invalid\n");
            continue;
        }

// printf("expand 3.1\n");

        new_puzzle_node = malloc(sizeof(nodes));

        total_nodes++;


        for(i=0; i<SIDE_LENGTH; i++){
            for(j=0; j<SIDE_LENGTH; j++){
                new_puzzle_node->state[i][j] = current_node->state[i][j];
            }
        }
        new_puzzle_node->hole_pos[0] = next_r_of_0;
        new_puzzle_node->hole_pos[1] = next_c_of_0;
        new_puzzle_node->state[row_of_0][column_of_0] = new_puzzle_node->state[next_r_of_0][next_c_of_0];
        new_puzzle_node->state[next_r_of_0][next_c_of_0] = 0;

        new_puzzle_node->move = move;
        // 減去原來的，加上新位置的 manhattan distance
        new_puzzle_node->heuristic = current_node->heuristic - manhattan_dis(current_node, next_r_of_0, next_c_of_0) + manhattan_dis(new_puzzle_node, row_of_0, column_of_0);
        
        // 只修改有影響到linear conflict的行或列
        if(new_puzzle_node->move == up || new_puzzle_node->move == down){
            new_puzzle_node->heuristic = new_puzzle_node->heuristic - (row_lc(current_node, row_of_0) + row_lc(current_node, next_r_of_0))*2
                                        + (row_lc(new_puzzle_node, row_of_0) + row_lc(new_puzzle_node, next_r_of_0))*2;
        }
        else{
            new_puzzle_node->heuristic = new_puzzle_node->heuristic - (col_lc(current_node, column_of_0) + col_lc(current_node, next_c_of_0))*2
                                        + (col_lc(new_puzzle_node, column_of_0) + col_lc(new_puzzle_node, next_c_of_0))*2;
        }
        
        new_puzzle_node->depth = current_node->depth + 1;
        new_puzzle_node->f = new_puzzle_node->heuristic + new_puzzle_node->depth;




// printf("threshold %d\n", threshold);
// fprintf(fp, "heuristic %d\n", new_puzzle_node->heuristic);
// fprintf(fp, "depth %d\n", new_puzzle_node->depth);
// fprintf(fp, "f %d\n", new_puzzle_node->f);
// fprintf(fp, "nodes now: %d\n", total_nodes);

// if(new_puzzle_node->f > bound){
    // for(i=0; i<SIDE_LENGTH; i++){
    //             for(j=0; j<SIDE_LENGTH; j++){
    //                 printf(" %2d", new_puzzle_node->state[i][j]);
    //             }
    //             printf("\n");
    // }
    // printf("\n\n");
//    Sleep(500);
// }


//---------------------------------------
// fprintf(fp, "heuristic %d\n", new_puzzle_node->heuristic);
// fprintf(fp, "depth %d\n", new_puzzle_node->depth);
// fprintf(fp, "f %d\n", new_puzzle_node->f);
// fprintf(fp, "nodes now: %d\n", total_nodes);

// for(i=0; i<SIDE_LENGTH; i++){
//             for(j=0; j<SIDE_LENGTH; j++){
//                 fprintf(fp, " %2d", new_puzzle_node->state[i][j]);
//             }
//             fprintf(fp, "\n");
// }
// fprintf(fp, "\n\n");
//---------------------------------------









// if(total_nodes%5000000 == 0){
//     printf("depth: %d\n", new_puzzle_node->depth);
//     printf("total nodes: %d\n", total_nodes);
// 	system("pause");
// }


        new_nodes[pos] = new_puzzle_node;
        pos++;
    }
    // printf("expand 3.2\n");


// printf("-----------------------\n");
// for(i=0; i<pos; i++){
//     if(new_nodes[i] == NULL){
//         printf(" 0 ");
//         continue;;
//     }
//     printf("%d ", new_nodes[i]->heuristic);
// }
// printf("\n---------------------\n");



    // bubble_sort(new_nodes, NEW_NODES_ARR_SIZE);
    bubble_sort(new_nodes, pos);
    // printf("expand 3.3\n");
}


int search(int threshold){
    static int t=0;
    // printf("\rthreshold %d, %d", threshold, t++);

    // printf(" s1\n");
    nodes *current = last_node->puzzle_node;
    nodes *new_nodes[NEW_NODES_ARR_SIZE]={NULL};
    int min, temp, i, j;

    if(current->f > threshold){
        // printf(" s1.1\n");
        return current->f;
    }
    if(at_goal(current) == True){
        found_goal_state = True;
        return -1;
    }

    // if(current->heuristic == 0){
    //     found_goal_state = True;
    //     return -1;
    // }

    // printf(" s2\n");

    min = infinite;

    expand_nodes(new_nodes);

    // printf("-----------------------\n");
    // for(i=0; i<NEW_NODES_ARR_SIZE; i++){
    //     if(new_nodes[i] == NULL){
    //         printf(" 0 ");
    //         continue;;
    //     }
    //     printf("%d ", new_nodes[i]->heuristic);
    // }
    // printf("\n---------------------\n");

    // printf(" s3\n");

    for(i=0; i<NEW_NODES_ARR_SIZE; i++){
        // printf(" s3.0\n");
        if(new_nodes[i] == NULL) break;;
        // printf(" s3.0.1\n");
        if(is_in_list(new_nodes[i]) == True){
            // printf(" s3.0.2\n");
            free(new_nodes[i]);
            continue;
        }
        

        // printf(" s3.1\n");
        list_append(new_nodes[i]);
        // printf(" s3.2\n");
        temp = search(threshold);
        // printf(" s3.2.1\n");
        if(found_goal_state == True) return -1;
        if(temp < min) min = temp;
        
        list_pop();
        free(new_nodes[i]);
    }

    return min;
}


void ida_star(nodes *current_node){
    int threshold = start_state->heuristic;
    int temp, t=0;

    if(at_goal(current_node) == True){
        found_goal_state = True;
        return;
    }
    list_append(current_node);

    // printf("1\n");

    while(1){
        // printf("1.5\n");
        temp = search(threshold);
        // printf("2\n");
        if(found_goal_state == True) return;
        else if(temp == infinite){
            printf("Not found\n");
            return;
        }
        // printf("3\n");
        threshold = temp;

        printf("\nthreshold in ida is: %d, %d, total nodes %llu", threshold, t, total_nodes);
        fprintf(fp, "\nthreshold in ida is: %d, %d, total nodes %llu", threshold, t, total_nodes);
        t++;
        total_nodes = 0;
    }
}



void report_solution(list *cur_node){
    if(cur_node->previous_node != NULL){
        report_solution(cur_node->previous_node);
        move_count++;
        switch (cur_node->puzzle_node->move){
            case up:
            printf("%2d    Move a tile down  | (= space up   )\n", move_count);
            fprintf(fp, "%2d    Move a tile down  | (= space up   )\n", move_count);
            break;
            
            case down:
            printf("%2d    Move a tile up    | (= space down )\n", move_count);
            fprintf(fp, "%2d    Move a tile up    | (= space down )\n", move_count);
            break;
            
            case left:
            printf("%2d    Move a tile right | (= space left )\n", move_count);
            fprintf(fp, "%2d    Move a tile right | (= space left )\n", move_count);
            break;
            
            case right:
            printf("%2d    Move a tile left  | (= space right)\n", move_count);
            fprintf(fp, "%2d    Move a tile left  | (= space right)\n", move_count);
            break;

            default:
            printf("      No moves required\n");
            fprintf(fp, "      No moves required\n");
            break;
        }
    }
}












int main(){
    nodes *current_node, *goal_node;
    clock_t begin, end;
    double total_time;
    fp = fopen("5by5_test.txt", "w");
    fprintf(fp, "The initial state:\n");

    set_goal_state();
    start_state = get_start_state();
    current_node = start_state;

    printf("Manhattan dis(l): %d\n", start_state->heuristic);
    fprintf(fp, "\nManhattan dis(l): %d\n", start_state->heuristic);

    // if(at_goal(start_state)){
    //     printf("\n\nSolution found: \n     No moves required\n");
    //     fprintf(fp, "\n\nSolution found: \n     No moves required\n");
    //     return 0;
    // }

    begin = clock();

    ida_star(current_node);

    end = clock();
    total_time = (double)(end - begin) / CLOCKS_PER_SEC;

    if(found_goal_state == True){
        printf("\n\nSolution found (%2d moves):\n", last_node->puzzle_node->depth);
        fprintf(fp, "\n\nSolution found (%2d moves):\n", last_node->puzzle_node->depth);
        report_solution(last_node);
        
    }
    else printf("not found");

    printf("\nDone!\n");
    fprintf(fp, "\nDone!\n");
    // printf("\ntotal expanded nodes: %d", total_nodes);
    // fprintf(fp, "\ntotal expanded nodes: %d", total_nodes);
    printf("\ntime used: %.3lf sec", total_time);
    fprintf(fp, "\ntime used: %.3lf sec", total_time);

    fclose(fp);

    return 0;
}

/*
2023/05/02
1. 修改 is_in_list 的function 使之效率更好
2. 修改linear conflict的判斷式 使效率更好
3. change total nodes to the total nodes in the current run in the ida function

2023/05/03
4. change total nodes's data type to unsigned long long
5. change the start check at_goal, if there's no move required, 
    then the function report_sol will print no moves required
6. change the list_pop function (maybe it will be faster) 
    and is_in_list function (add int to_break to leave the loop faster)
7. change row_ls and col_lc function
8. change expand>bubble_sort, the second parameter change to pos (original is NEW_NODES_ARR_SIZE)

TODO: 測試老師給的5*5測資
TODO: maybe change the bubble sort to quick sort (just maybe)
*/