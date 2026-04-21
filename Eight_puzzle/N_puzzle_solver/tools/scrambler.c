#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
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
unsigned long long total_moves = 0;



void set_goal_state(int current_state[][SIDE_LENGTH]){
    int i, j, num=1;
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++, num++){
            if(i==SIDE_LENGTH-1 && j==SIDE_LENGTH-1) num = 0;
            current_state[i][j] = num;
        }
    }
}


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void scramble(int current_state[][SIDE_LENGTH], unsigned long long user_moves, int user_seed){
    srand(user_seed);
    moves direction, last_direction=-1;
    zero_pos hole = {.x = SIDE_LENGTH-1, .y = SIDE_LENGTH-1};

    while(total_moves < user_moves){
        direction = rand() % 4;

        if(last_direction == direction) continue;
        last_direction = direction;


        switch(direction){
            case up:
            if(hole.y == 0) continue;
            move_UP;
            hole.y--;
            break;
            
            case down:
            if(hole.y == SIDE_LENGTH-1) continue;
            move_DOWN;
            hole.y++;
            break;
            
            case left:
            if(hole.x == 0) continue;
            move_LEFT;
            hole.x--;
            break;
            
            case right:
            if(hole.x == SIDE_LENGTH-1) continue;
            move_RIGHT;
            hole.x++;
            break;
        }
        
        total_moves++;
    }
    
}


int main(){
    unsigned long long user_moves;
    unsigned int user_seed;
    int i, j, pad;
    FILE *ini;
    
    printf("Enter puzzle size (NO LIMIT): ");
    scanf("%d", &SIDE_LENGTH);
    
    printf("Enter moves (less than 18,446,744,073,709,551,615): ");
    scanf("%llu", &user_moves);
    
    printf("Enter seed: ");
    scanf("%d", &user_seed);

    int puzzle_state[SIDE_LENGTH][SIDE_LENGTH];

    if(SIDE_LENGTH > 31) pad = 4;
    else if(SIDE_LENGTH > 99) pad = 5;
    else pad = 3;


    set_goal_state(puzzle_state);

    scramble(puzzle_state, user_moves, user_seed);


    ini = fopen("ini.txt", "w");
    fprintf(ini, "%*d\n", pad, SIDE_LENGTH);

    printf("\n");
    for(i=0; i<SIDE_LENGTH; i++){
        for(j=0; j<SIDE_LENGTH; j++){
            printf("%*d ", pad, puzzle_state[i][j]);
            fprintf(ini, "%*d ", pad, puzzle_state[i][j]);
        }
        printf("\n");
        fprintf(ini, "\n");
    }
    printf("\n");

    fclose(ini);
    system("pause");
    
    return 0;
}