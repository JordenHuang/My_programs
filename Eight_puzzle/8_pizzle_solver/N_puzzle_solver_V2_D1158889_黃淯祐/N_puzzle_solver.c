#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "N_puzzle_data_structure.c"


#define MAX_LENGTH 17

/*
#define move_UP swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]-1][zero_pos[0]])
#define move_DOWN swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]+1][zero_pos[0]])
#define move_RIGHT swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]][zero_pos[0]+1]);
#define move_LEFT swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]][zero_pos[0]-1]);
*/


#define move_UP    (\
                    {\
                        swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]-1][zero_pos[0]]);\
                        zero_pos[1] -= 1;\
                        list_append(up);\
                        move_count++;\
                    }\
                    )
#define move_DOWN  (\
                    {\
                        swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]+1][zero_pos[0]]);\
                        zero_pos[1] += 1;\
                        list_append(down);\
                        move_count++;\
                    }\
                    )
                    
#define move_RIGHT (\
                    {\
                        swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]][zero_pos[0]+1]);\
                        zero_pos[0] += 1;\
                        list_append(right);\
                        move_count++;\
                    }\
                    )
#define move_LEFT  (\
                    {\
                        swap(&current_state[zero_pos[1]][zero_pos[0]], &current_state[zero_pos[1]][zero_pos[0]-1]);\
                        zero_pos[0] -= 1;\
                        list_append(left);\
                        move_count++;\
                    }\
                    )
//*/


//---linked list part----------------------------------------------------------------------------------------//

list *list_head = NULL;  // global list----------------------------------------------------------------------//
list * list_last_node = NULL;

void list_append(moves cur_move){
    // create a new node of list and assign data into it
    list *new_node = malloc(sizeof(list));
    new_node->move = cur_move;
    new_node->next_node = NULL;
        
    if(list_head == NULL){
        list_head = new_node;
    }
    else{
        list_last_node->next_node = new_node;
    }

    list_last_node = new_node;
}


void list_clear(){
    list *current=list_head, *next=list_head->next_node;

    while(next != NULL){
        free(current);
        current = next;
        next = current->next_node;
    }
    free(current);
}


//---stack part----------------------------------------------------------------------------------------------//

stack *stack_top = NULL;

void stack_push(moves cur_move){
    stack *new_node = malloc(sizeof(stack));
    new_node->move = cur_move;

    if(stack_top == NULL){
        stack_top = new_node;
        new_node->next_node = NULL;
        return;
    }

    new_node->next_node = stack_top;
    stack_top = new_node;
}


moves stack_pop(){
    stack *poped_node = stack_top;
    moves poped_data = stack_top->move;

    stack_top = stack_top->next_node;
    free(poped_node);

    return poped_data;
}


boool stack_empty(){
    if(stack_top == NULL) return True;
    else return False;
}


//-----------------------------------------------------------------------------------------------------------//

int SIDE_LENGTH = 3;

int goal_state[MAX_LENGTH][MAX_LENGTH];
int current_state[MAX_LENGTH][MAX_LENGTH];
int move_count = 0;
int swap_times = 0;

int zero_pos[2];  // [0] for x pos, [1] for y pos
int buffer_pos[2];

boool solved = False;

FILE *ini;
FILE *fp;



void set_goal_state(){
    int i, j, num=1;
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++, num++){
            if(i==SIDE_LENGTH-1 && j==SIDE_LENGTH-1) num = 0;
            goal_state[i][j] = num;
        }
    }
}


boool at_goal(){
    int i, j;

    for (i = 0; i < SIDE_LENGTH; i++)
        for (j = 0; j < SIDE_LENGTH; j++)
            if ((current_state[i][j]) != goal_state[i][j]){
                return False;
            }

    return True;
}


void get_initial_state(){
    int  i, j, n=0;
    char check[8]={'\0'};  // just for store user choise
    

    while(1){
        for(i=0; i<SIDE_LENGTH; i++){
            for(j=0; j<SIDE_LENGTH; j++){
                fscanf(ini, "%d", &current_state[i][j]);
            }
        }

        printf("\nStarting configuration is: \n");
        for (i=0; i<SIDE_LENGTH; i++){
            printf("     ");
            for (j=0; j<SIDE_LENGTH; j++) printf(" %3d", current_state[i][j]);
            printf("\n");
        }
        printf("\nIs that correct? (n: quit program / else to continue): ");
        gets(check);
        

        if((check[0] == 'n') || (check[0] == 'N')){
            fclose(ini);
            printf("Quit program\n");
            system("pause");
            exit(1);
        }

        break;
    }


    // set the 0 position to the zero_pos array
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            if(current_state[i][j] == 0){
                zero_pos[0] = j;  // x pos is column
                zero_pos[1] = i;  // y pos is row
                return;
            }
        }
    }
}


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void four_move_swap(){
    move_RIGHT;
    move_UP;
    move_LEFT;
    move_DOWN;
    swap_times++;
}


void get_target_pos(int target_num, int target_pos[2]){
    int i, j;
    // printf("target num: %d\n", target_num);
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            if(goal_state[i][j] == target_num){
                target_pos[0] = j;
                target_pos[1] = i;
                return;
            }
        }
    }
}


void initialize_buffer(){
    // printf("zero pos x: %d\n", zero_pos[0]);

    // normal case
    if(zero_pos[0] != SIDE_LENGTH-1){
        // move right to (SIDE_LENGTH-2)
        while(zero_pos[0] != SIDE_LENGTH-2){
            move_RIGHT;
        }

        // move down to (SIDE_LENGTH-1)
        while(zero_pos[1] != SIDE_LENGTH-1){
            move_DOWN;
        }
    }

    // at the last column case
    else{
        move_LEFT;

        while(zero_pos[1] != SIDE_LENGTH-1){
            move_DOWN;

        }
    }
}


void set_up_move(int to_solve){
    // printf("to solve is: %d\n", to_solve);
    int target_pos[2], ud_bound, rl_bound;

    get_target_pos(to_solve, target_pos);

    ud_bound = target_pos[1];  // y pos
    rl_bound = target_pos[0];  // x pos


    // if to_solve at (SIDE_LENGTH-2) column
    // needs to give an extra left row(column) for space to move around, so rl_bound-1
    if((to_solve % SIDE_LENGTH == SIDE_LENGTH-1)){
        rl_bound -= 1;
    }

    // if to_solve's goal pos is at the last row
    // needs to give an extra upper column(row) for space to move around, so ud_bound-1
    if((to_solve-1) / SIDE_LENGTH == SIDE_LENGTH-1){
        ud_bound -= 1;
    }    
    

    while((target_pos[0] != buffer_pos[0]) || (target_pos[1] != buffer_pos[1])){
        while(zero_pos[1] != ud_bound){
            move_UP;
            stack_push(up);
            // printf("up\n");
        }
        while(zero_pos[0] != rl_bound){
            move_LEFT;
            stack_push(left);
            // printf("left\n");
        }
        while(zero_pos[1] != SIDE_LENGTH-1){
            move_DOWN;
            stack_push(down);
            // printf("down\n");
        }
        while(zero_pos[0] != buffer_pos[0]){
            move_RIGHT;
            stack_push(right);
            // printf("right\n");
        }

        // update target pos

        // (a little bit special case)
        // if target's row is at (SIDE_LENGTH -1) = last row
        // then target will move up, so (row - 1)
        if(target_pos[1] == SIDE_LENGTH-1){
                target_pos[1] -= 1;
                continue;
            }

        // if target's column position != buffer's column position
        // then the target will move right, so (column + 1)
        if(target_pos[0] != buffer_pos[0]){
            target_pos[0] += 1;
        }
        // else if the target's row position != to buffer's row position
        // then the target will move down, so(row + 1)
        else if(target_pos[1] != buffer_pos[1]){
            target_pos[1] += 1;
        }
    }
}

void undo_set_up_move(){
    moves undo_move;
    int target_pos[2];

    while(stack_empty() == False){
        undo_move = stack_pop();
        switch(undo_move){
            case up:
                move_DOWN;
                break;
                
            case down:
                move_UP;
                break;
                
            case left:
                move_RIGHT;
                break;
                
            case right:
                move_LEFT;
                break;
        }
    }
}


void last_column_case(int to_solve){
    int target_pos[2], ud_bound, rl_bound;
    get_target_pos(to_solve, target_pos);

    ud_bound = target_pos[1];  // y pos
    rl_bound = target_pos[0];  // x pos

    // calculate set up moves
    int set_up_moves = abs(target_pos[0] - buffer_pos[0]) + abs(target_pos[1] - buffer_pos[1]);
    int counter = 0;

    while(counter < set_up_moves){
        while(zero_pos[1] != ud_bound+1){
            move_UP;
            stack_push(up);
        }

        move_RIGHT;
        stack_push(right);

        move_UP;
        stack_push(up);

        move_LEFT;
        stack_push(left);
        move_LEFT;
        stack_push(left);
        
        while(zero_pos[1] != SIDE_LENGTH-1){
            move_DOWN;
            stack_push(down);
        }

        move_RIGHT;
        stack_push(right);
        
        counter++;
    }
    four_move_swap();
    undo_set_up_move();
    four_move_swap();
}


void special_case_swap(int to_solve){
    int like_11 = goal_state[SIDE_LENGTH-2][SIDE_LENGTH-2];
    int like_12 = goal_state[SIDE_LENGTH-2][SIDE_LENGTH-1];

    if(to_solve == like_11){
        if(swap_times % 2 == 1){
            move_RIGHT;
            move_UP;
            move_LEFT;
            move_DOWN;
        }
        else{
            move_UP;
            move_RIGHT;
            move_DOWN;
            move_LEFT;
        }
    }
    else{
        if(swap_times % 2 == 1){
            move_UP;
            move_RIGHT;
            move_DOWN;
            move_LEFT;
        }
        else{
            move_RIGHT;
            move_UP;
            move_LEFT;
            move_DOWN;
        }
    }
    swap_times++;
}


void swap_with_unsolved(){
    // set the num = (max number in the puzzle -1)
    // then check if the num is solved
    // if not sovled, than the tile 15 will swap to that position
    // to solve the spacial tile 15 case

    int num = SIDE_LENGTH*SIDE_LENGTH-2;
    boool not_solved = False;
    while(not_solved == False){
        if(current_state[(num-1)/SIDE_LENGTH][(num-1)%SIDE_LENGTH] == goal_state[(num-1)/SIDE_LENGTH][(num-1)%SIDE_LENGTH]){
            num -= 1;
            // 排除 tile 11 or 12 case
            if(num == goal_state[SIDE_LENGTH-2][SIDE_LENGTH-1]){
                num -= 2;
            }
            continue;
        }
        else not_solved = True;
    }

    // if to swapped tile is at last column
    if(goal_state[(num-1)/SIDE_LENGTH][(num-1)%SIDE_LENGTH] % SIDE_LENGTH == 0){
        last_column_case(goal_state[(num-1)/SIDE_LENGTH][(num-1)%SIDE_LENGTH]);
    }
    // else normal case
    else{
    set_up_move(goal_state[(num-1)/SIDE_LENGTH][(num-1)%SIDE_LENGTH]);
    four_move_swap();
    undo_set_up_move();
    four_move_swap();
    }
}


void eight_puzzle_tile_3(){
    // move right (set up)
    move_RIGHT;
    // then do the algorithm
    move_UP;
    move_UP;
    move_LEFT;
    move_DOWN;
    move_DOWN;
    move_RIGHT;
    move_UP;
    move_LEFT;
    move_UP;
    move_RIGHT;
    move_DOWN;
    move_LEFT;
    move_DOWN;
    // no need to move left back (undo set up), because the space is now at the buffer pos
}





// /*
void solver(){
    int i, j;
    int to_solve;

    initialize_buffer();

    // for (i=0; i<SIDE_LENGTH; i++){
    //     printf("     ");
    //     for (j=0; j<SIDE_LENGTH; j++) printf(" %3d", current_state[i][j]);
    //     printf("\n");
    // }

    while(1){
        to_solve = current_state[SIDE_LENGTH-1][SIDE_LENGTH-1];
        // printf("to_solve is: %d\n", to_solve);

        // if to_solve = 11 or 12
        if((to_solve == goal_state[SIDE_LENGTH-2][SIDE_LENGTH-2]) || (to_solve == goal_state[SIDE_LENGTH-2][SIDE_LENGTH-1])){
            // printf("11 or 12 case\n");
            special_case_swap(to_solve);
        }
        // if to_solve = 15
        else if(to_solve == SIDE_LENGTH*SIDE_LENGTH - 1){
            // all solved case
            if(at_goal() == True){
                move_RIGHT;
                break;
            }
            // tile 15 case
            else{
                // printf("15 case\n");
                swap_with_unsolved();
                continue;
            }
        }
        // if to_solve's goal position is at the last column case, like 4 or 8
        // tile 4 or tile 8 case
        else if(to_solve % SIDE_LENGTH == 0){
            // printf("last column case\n");
            // if to_solve is like tile 8
            if(to_solve == goal_state[SIDE_LENGTH-3][SIDE_LENGTH-1]){
                eight_puzzle_tile_3();
            }
            // for other last column cases
            else{
                last_column_case(to_solve);
            }
        }
        else{
            // printf("normal case\n");
            set_up_move(to_solve);
            four_move_swap();
            undo_set_up_move();
            four_move_swap();
        }
    }
}


void report_solution(){
    fp = fopen("move.txt", "w");

    list *cur = list_head;
    while(cur != NULL){
        switch(cur->move){
            case up:
                fprintf(fp, "D\n");
                break;
            
            case down:
                fprintf(fp, "U\n");
                break;
            
            case left:
                fprintf(fp, "R\n");
                break;
            
            case right:
                fprintf(fp, "L\n");
                break;
        }
        cur = cur->next_node;
    }

    fclose(fp);
}


void show_solution_on_screen(){
    list *cur = list_head;
    move_count = 1;
    
    while(cur != NULL){
        switch(cur->move){
            case up:
                printf("%2d    Move a tile down  | (= space up   )\n", move_count);
                break;
            
            case down:
                printf("%2d    Move a tile up    | (= space down )\n", move_count);
                break;
            
            case left:
                printf("%2d    Move a tile right | (= space left )\n", move_count);
                break;
            
            case right:
                printf("%2d    Move a tile left  | (= space right)\n", move_count);
                break;
        }
        move_count++;
        cur = cur->next_node;
    }
}



int main(){
    clock_t begin, end;
    double total_time;
    int i, j;

    ini = fopen("ini.txt", "r");

    if(ini == NULL){
        printf("CANNOT open file to read initial state!");
        exit(1);
    }

    // read the board size from the file
    fscanf(ini, "%d\n", &SIDE_LENGTH);


    buffer_pos[0] = SIDE_LENGTH-2;
    buffer_pos[1] = SIDE_LENGTH-2;

    set_goal_state();

    get_initial_state();
    
    // 交換goal state 裡0 跟15 的位置
    swap(&goal_state[SIDE_LENGTH-1][SIDE_LENGTH-2], &goal_state[SIDE_LENGTH-1][SIDE_LENGTH-1]);  


    begin = clock();

    solver();

    end = clock();
    total_time = (double)(end - begin) / CLOCKS_PER_SEC;


    report_solution();

    printf("\nSolution found!\n");
    printf("time used  : %.3lf sec\n", total_time);
    printf("Total moves: %d\n", move_count);
    printf("\nShow the moves on screen (1/0)? ");
    scanf("%d", &i);
    if(i == 1){
        show_solution_on_screen();
    }


    // printf("\nFinal state is:\n");
    // for (i=0; i<SIDE_LENGTH; i++){
    //     printf("     ");
    //     for (j=0; j<SIDE_LENGTH; j++) printf(" %3d", current_state[i][j]);
    //     printf("\n");
    // }


    list_clear();

    fclose(ini);
    
    printf("\n");
    system("pause");
    
    return 0;
}