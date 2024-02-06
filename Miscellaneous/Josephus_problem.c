#include <stdio.h>

#define LEN 41
#define STEP 3

int find_next(int soldier[], int now){
    while(1){
        if(soldier[now] == 0) now = (now+1) % LEN;
        else return now;
    }
}

int killing_order(int order[], int soldiers[]){
    int i = -1, round = 0, c = 0, j;
    while(round != LEN){
        for(c=0; c<STEP; c++){
            i = find_next(soldiers, (i+1) % LEN);
        }
        soldiers[i] = 0;
        round++;
        order[i] = round;

        // for(j=0; j<LEN; j++){
        //     printf("%2d ", soldiers[j]);
        // }
        // printf("\n");
        // for(j=0; j<LEN; j++){
        //     printf("%2d ", order[j]);
        // }
        // printf("\n");
    }

    // return index (i + 1) to present the soldier's number
    return i+1;
}

int main(){
    int soldiers[LEN], order[LEN] = {0};
    int i, last;

    printf("The soldiers' number: \n");
    for(i=0; i<LEN; i++){
        soldiers[i] = i+1;
        printf("%2d ", soldiers[i]);
    }

    printf("\nThe KILLING order: \n");
    last = killing_order(order, soldiers);
    for(i=0; i<LEN; i++){
        printf("%2d ", order[i]);
    }

    printf("\nThe last soldier is: %d", last);

    return 0;
}