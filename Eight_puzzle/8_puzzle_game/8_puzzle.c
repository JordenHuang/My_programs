#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define UP -N
#define RIGHT 1
#define DOWN N
#define LEFT -1

#define SIZE N*N

int N=3;
int space_position = 0;
int moves=0;



void swap(int board[], int index_a, int index_b){
    int temp;
    temp = board[index_a];
    board[index_a] = board[index_b];
    board[index_b] = temp;
    space_position = index_b;
}


void scramble(int board[]){
    srand(time(NULL));
    int swap_times = rand()%300 + 150;  // �@�}�l���ê�����
    int i, quotient, remain, direction;  // quotient�Orow, remain�Ocolumn
    for(i=0; i<swap_times; i++){
        quotient = space_position/N;
        remain = space_position%N;
        if( (quotient+1 == N || quotient-1 < 0) && (remain+1 == N || remain-1 < 0) ){  // the space is at corner
            direction = rand()%2;
            if(quotient-1 < 0  && remain-1 < 0){  // if at left up
                switch(direction){
                    case 0: swap(board, space_position, space_position+RIGHT);break;
                    case 1: swap(board, space_position, space_position+DOWN);break;
                }
            }
            else if(quotient-1 < 0  && remain+1 == N){  // at right up
                switch(direction){
                    case 0: swap(board, space_position, space_position+DOWN);break;
                    case 1: swap(board, space_position, space_position+LEFT);break;
                }
            }
            else if(quotient+1 == N  && remain+1 == N){  // at right down
                switch(direction){
                    case 0: swap(board, space_position, space_position+UP);break;
                    case 1: swap(board, space_position, space_position+LEFT);break;
                }
            }
            else{  // at left down
                switch(direction){
                    case 0: swap(board, space_position, space_position+UP);break;
                    case 1: swap(board, space_position, space_position+RIGHT);break;
                }
            }
        }
        else if(quotient+1 == N || quotient-1 < 0 || remain+1 == N || remain-1 < 0){ // the space is at edge
            direction = rand()%3;
            if(quotient-1 < 0){  // at top
                switch(direction){
                    case 0: swap(board, space_position, space_position+RIGHT);break;
                    case 1: swap(board, space_position, space_position+DOWN);break;
                    case 2: swap(board, space_position, space_position+LEFT);break;
                }
            }
            else if(remain+1 == N){  // at right
                switch(direction){
                    case 0: swap(board, space_position, space_position+DOWN);break;
                    case 1: swap(board, space_position, space_position+LEFT);break;
                    case 2: swap(board, space_position, space_position+UP);break;
                }
            }
            else if(quotient+1 == N){  // at bottom
                switch(direction){
                    case 0: swap(board, space_position, space_position+LEFT);break;
                    case 1: swap(board, space_position, space_position+UP);break;
                    case 2: swap(board, space_position, space_position+RIGHT);break;
                }
            }
            else{
                switch(direction){  // at left
                    case 0: swap(board, space_position, space_position+UP);break;
                    case 1: swap(board, space_position, space_position+RIGHT);break;
                    case 2: swap(board, space_position, space_position+DOWN);break;
                }
            }
        }
        else{  // the space is not at corner and edge
            direction = rand()%4;
            switch(direction){
                case 0: swap(board, space_position, space_position+UP);break;
                case 1: swap(board, space_position, space_position+RIGHT);break;
                case 2: swap(board, space_position, space_position+DOWN);break;
                case 3: swap(board, space_position, space_position+LEFT);break;
            }
        }
    }
}



int valid_direction(int board[], int move_direction){
    int quotient = space_position/N;
    int remain = space_position%N;
    if( (quotient+1 == N || quotient-1 < 0) && (remain+1 == N || remain-1 < 0) ){  // the space is at corner
        if(quotient-1 < 0  && remain-1 < 0){  // if at left up
            switch(move_direction){
                case 0: return 0;
                case 1: return 1;
                case 2: return 1;
                case 3: return 0;
            }
        }
        else if(quotient-1 < 0  && remain+1 == N){  // at right up
            switch(move_direction){
                case 0: return 0;
                case 1: return 0;
                case 2: return 1;
                case 3: return 1;
            }
        }
        else if(quotient+1 == N  && remain+1 == N){  // at right down
            switch(move_direction){
                case 0: return 1;
                case 1: return 0;
                case 2: return 0;
                case 3: return 1;
            }
        }
        else{  // at left down
            switch(move_direction){
                case 0: return 1;
                case 1: return 1;
                case 2: return 0;
                case 3: return 0;
            }
        }
    }
    else if(quotient+1 == N || quotient-1 < 0 || remain+1 == N || remain-1 < 0){ // the space is at edge
        if(quotient-1 < 0){  // at top
            switch(move_direction){
                case 0: return 0;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
            }
        }
        else if(remain+1 == N){  // at right
            switch(move_direction){
                case 0: return 1;
                case 1: return 0;
                case 2: return 1;
                case 3: return 1;
            }
        }
        else if(quotient+1 == N){  // at bottom
            switch(move_direction){
                case 0: return 1;
                case 1: return 1;
                case 2: return 0;
                case 3: return 1;
            }
        }
        else{
            switch(move_direction){  // at left
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 0;
            }
        }
    }
    else{  // the space is not at corner and edge
        switch(move_direction){
            case 0: return 1;  // up
            case 1: return 1;  // right
            case 2: return 1;  // down
            case 3: return 1;  // left
        }
    }
}


void user_input(int board[]){
    int move = getch();
    if(move == 27){
        printf("\nQuit");
        exit(0);
    }
    if(move == 224){
        move=getch();
        switch(move){
            case 72:
                // printf("UP");
                if( valid_direction(board, 0)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+UP);
                moves++;
                break;
            case 77:
                // printf("RIGHT");
                if( valid_direction(board, 1)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+RIGHT);
                moves++;
                break;
            case 80:
                // printf("DOWN");
                if( valid_direction(board, 2)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+DOWN);
                moves++;
                break;
            case 75:
                // printf("LEFT");
                if( valid_direction(board, 3)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+LEFT);
                moves++;
                break;
            
            default:
                user_input(board);
        }
    }
    else{
        switch(move){
            case 119:
                // printf("UP");
                if( valid_direction(board, 0)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+UP);
                moves++;
                break;

            case 100:
                // printf("RIGHT");
                if( valid_direction(board, 1)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+RIGHT);
                moves++;
                break;

            case 115:
                // printf("DOWN");
                if( valid_direction(board, 2)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+DOWN);
                moves++;
                break;

            case 97:
                // printf("LEFT");
                if( valid_direction(board, 3)==0 ){
                    user_input(board);
                    break;
                }
                swap(board, space_position, space_position+LEFT);
                moves++;
                break;
            
            default:
                user_input(board);
        }
    }
}


int end_game(int board[], int solved_board[]){
    int i;

    for(i=0; i<SIZE; i++){
        if(board[i] != solved_board[i]){
            return 0;
        }
    }

    return 1;
}



int main(){
    while(1){
        printf("8 puzzla game!!\n");
        printf("Enter the side length N (N must bigger than 2, enter -1 to quit): ");
        scanf("%d", &N);
        while(getchar() != '\n') continue;  // Ū���bbuffer�̳Ѿl���r��
        if(N==-1){
            printf("Bye");
            exit(0);
        }
        else if(N==1){
            printf("Too small, enter again\n");
            //while(getchar() != '\n') continue;
            Sleep(500);
            continue;
        }
        else if(N>10){
            printf("Are you sure?\n");
            Sleep(800);
            printf("Let's Go!!\n");
            Sleep(800);
        }
        //printf("Use arrow keys or WASD keys to move, ESC to quit");
        //Sleep(1200);

        int solved_board[SIZE];
        int board[SIZE];
        int i, j, end=0;
        time_t start_time, end_time;
        double total_time;
        moves=0;
        

        i = SIZE-1;
        solved_board[i] = 0;
        board[i] = 0;
        for(i=0, j=1; i<SIZE-1; i++, j++){  // ��l�ƴѽL
            solved_board[i] = j;
            board[i] = solved_board[i];
        }

        
        space_position=SIZE-1;  // ��l��space����m

        scramble(board);  // ���ôѽL

        while(end!=1){
            printf("\x1b[2J\n");

            for(i=0, j=0; i<SIZE+N; i++){  // ��X�ѽL  // size+N �O�]���h�F���檺column
                if(i==1){
                    printf("\033[H");
                    printf("Use arrow keys or WASD keys to move, ESC to quit\n\n");
                }
                
                if(i%(N+1) != 0){
                    if(board[j]==0){
                        if(N>10) printf("   ��");
                        else printf("  ��");
                    }
                    else{
                        if(N>10) printf(" %3d", board[j]);
                        else printf(" %2d", board[j]);
                    }
                    j++;
                }
                else{
                    printf("\n");
                }
            }
            printf("\n\n");

            end = end_game(board, solved_board);  // �P�_�O�_����
            if(end==1){
                time(&end_time);
                printf(" SOLVED!!\n\n");
                total_time = difftime(end_time, start_time);
                printf("Total time: %.3f seconds\n", total_time);
                printf("Total moves: %d\n\n", moves);
                break;
            }

            user_input(board);  // �ϥΪ̿�J

            if(moves==1){
                time(&start_time);
            }

            printf("\x1b[H");
        }
    }
}


/*  �Q�k:
1. ����l�ƨ�ӴѽL, �@�ӷ�@�̫᧹�������, ���̥��åt�@�ӡC
2. ���ë��X, ���ݨϥΪ̿�J, �P�_��J�O�_�����i�檺���ʤ�V�Υ��T����J, ���ʫ�M�ŵe���A��X�ѽL�C
3. �C�@�����ʧ����ˬd�O�_�����C��, �Y����, �̫���ܪ�O���ɶ���B��

TODO: time is only ���, �i�H��令��T��@��

*/