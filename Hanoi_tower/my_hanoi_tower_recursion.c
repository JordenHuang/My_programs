#include <stdio.h>
#include <stdlib.h>

int step=1;

int mover(char source, char destination, int plate);

int main(){
    int plate;

    printf("This program shows the solution for the Hanio tower with recursion\n");
    printf("Put all the plates from A to C while bigger plates is always under the smaller plates\n");
    printf("Enter the number of plates: ");
    scanf("%d", &plate);

    if (plate<1){
        printf("Plate number must bigger or equal than 1 !!");
        exit(0);
    }

    //mover('A', 'C', plate);
    printf("Total move count is: %d", mover('A', 'C', plate));
    
    return 0;
}


int mover(char source, char destination, int plate){
    char A='A', B='B', C='C';
    char next_dest;
    int move_counts=0;

    if ((source==A && destination==C) || (source==C && destination==A)){
        next_dest=B;
    }
    else if ((source==A && destination==B) || (source==B && destination==A)){
        next_dest=C;
    }
    else if ((source==B && destination==C) || (source==C && destination==B)){
        next_dest=A;
    }

    if (plate==1){
        printf("Step %2d: put %c to %c\n", step, source, destination);
        step++;
        move_counts=1;
        return move_counts;
    }
    else{
        move_counts = mover(source, next_dest, plate-1) + mover(source, destination, 1) + mover(next_dest, destination, plate-1);
    }

    return move_counts;
}


/* count total moves  // it can be easier with the function: 2^plate -1
    if (plate==1){
        printf("Put %c to %c", source, destination);
        return 1;
    }
    else{
        return 2 * mover('A', 'C', plate-1) + 1;
    }
*/