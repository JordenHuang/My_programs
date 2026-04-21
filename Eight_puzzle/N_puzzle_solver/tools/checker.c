#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define move_UP swap(&current_state[hole.y][hole.x], &current_state[hole.y-1][hole.x])
#define move_DOWN swap(&current_state[hole.y][hole.x], &current_state[hole.y+1][hole.x])
#define move_RIGHT swap(&current_state[hole.y][hole.x], &current_state[hole.y][hole.x+1]);
#define move_LEFT swap(&current_state[hole.y][hole.x], &current_state[hole.y][hole.x-1]);


enum move_type{up=0, down, left, right};
enum Bool_type{False, True};

struct zero_pos{
    int x;
    int y;
};

typedef enum Bool_type boool;
typedef enum move_type moves;
typedef struct zero_pos zero_pos;


int SIDE_LENGTH;


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


boool at_goal(int current_state[][SIDE_LENGTH]){
    int i, j, num=1;

    for (i = 0; i < SIDE_LENGTH; i++){
        for (j = 0; j < SIDE_LENGTH; j++){
            if (((current_state[i][j]) != num) && !(i == SIDE_LENGTH-1 && j == SIDE_LENGTH-1)){
                return False;
            }
            else if(i == SIDE_LENGTH-1 && j == SIDE_LENGTH-1){
                if(current_state[i][j] == 0) return True;
            }

            num++;
        }
    }

    return True;
}


void solver(FILE *sol_fp, int current_state[][SIDE_LENGTH], zero_pos hole){
    // moves direction;
    char c;

    while(!feof(sol_fp)){
        fscanf(sol_fp, "%c\n", &c);
        // printf("c is: %c\n", c);
        switch(c){
            case 'D':
            move_UP;
            hole.y--;
            break;
            
            case 'U':
            move_DOWN;
            hole.y++;
            break;
            
            case 'R':
            move_LEFT;
            hole.x--;
            break;
            
            case 'L':
            move_RIGHT;
            hole.x++;
            break;
        }
        // printf("x: %d\n", hole.x);
        // printf("y: %d\n", hole.y);
    }
}

int main(){
    // const char *init_state_filename = "scramble/3x3.txt";
    const char *init_state_filename = "scramble/4x4.txt";
    // const char *init_state_filename = "scramble/5x5.txt";
    // const char *init_state_filename = "scramble/7x7.txt";
    // const char *init_state_filename = "scramble/13x13.txt";
    // const char *init_state_filename = "scramble/15x15.txt";
    // const char *init_state_filename = "scramble/17x17.txt";
    // const char *init_state_filename = "scramble/28x28.txt";

    const char *solution_filename = "scramble/solution/sol.txt";

    FILE *sol_fp = fopen(solution_filename, "r");
    if (sol_fp == NULL) {
        fprintf(stderr, "Can not open file %s\n", solution_filename);
        exit(1);
    }

    FILE *ini = fopen(init_state_filename, "r");
    if (ini == NULL) {
        fprintf(stderr, "Can not open file %s\n", init_state_filename);
        exit(1);
    }

    fscanf(ini, "%d", &SIDE_LENGTH);
    // printf("The side len is %d\n", SIDE_LENGTH);

    int puzzle_state[SIDE_LENGTH][SIDE_LENGTH];
    int i, j, pad;
    zero_pos hole;

    if(SIDE_LENGTH > 31) pad = 4;
    else if(SIDE_LENGTH > 99) pad = 5;
    else pad = 3;


    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            fscanf(ini, "%d", &puzzle_state[i][j]);
            if(puzzle_state[i][j] == 0){
                hole.x = j;
                hole.y = i;
            }
        }
    }

    printf("Initial state:\n");
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            printf("%*d ", pad, puzzle_state[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");


    solver(sol_fp, puzzle_state, hole);


    printf("Result:\n");
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            printf("%*d ", pad, puzzle_state[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    
    if(at_goal(puzzle_state) == True) printf("The result is CORRECT\n");
    else printf("The result is INCORRECT\n");

    printf("\n");

    fclose(ini);
    fclose(sol_fp);

    system("pause");

    return 0;
}
