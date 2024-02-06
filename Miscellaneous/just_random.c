#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define LETTER_LENGTH 96
#define TARGET_PATTERN_LENGTH 100
#define DELAY 10

/*
Ascii code:
    65(A) ~ 90(Z)
    97(a) ~ 122(z)
    
    All printable characters:
        32( ) ~ 126(~)
*/

void create_letter_array(char *letters){
    int index, c;
    for(index=0, c='A'; c<='Z'; index++, c++){
        letters[index] = c;
    }
    for(index, c='a'; c<='z'; index++, c++){
        letters[index] = c;
    }
}

void create_ascii_printable_character(char *letters){
    int i;
    for(i=' '; i <= '~'; i++){
        letters[i-32] = i;
    }
}


void display_only_finded(char *target_pattern, char *letters){
    int length, i, running_index, finded_index;

    length = strlen(target_pattern);

    for(i=0; i<length; i++){
        for(running_index=0; letters[running_index] <= target_pattern[i]; running_index++){
            printf("\r");
            for(finded_index=0; finded_index < i; finded_index++){
                printf("%c", target_pattern[finded_index]);
            }
            printf("%c", letters[running_index]);
            Sleep(DELAY);
        }
        // printf("\n");
    }
}

void display_all_cols(char *target_pattern, char *letters){
    int length, i, running_index, finded_index, rand_pos;

    length = strlen(target_pattern);
    srand((unsigned)time(NULL));

    for(i=0; i<length; i++){
        for(running_index=0; letters[running_index] <= target_pattern[i]; running_index++){
            printf("\r");
            for(finded_index=0; finded_index < i; finded_index++){
                printf("%c", target_pattern[finded_index]);
            }

            printf("%c", letters[running_index]);

            rand_pos = rand() % LETTER_LENGTH;
            for(finded_index; finded_index+2 < length; finded_index++){
                printf("%c", letters[rand_pos++]);
            }

            printf("\t");

            Sleep(DELAY);
        }
        // printf("\n");
    }
}

void display_random_position(char *target_pattern, char *letters){
    int target_pattern_length = strlen(target_pattern) - 1;
    int rand_pos, rand_pos2, i, running_index, finded_index;
    srand((unsigned)time(NULL));

    // print already finded string
    for(i=0; i < target_pattern_length; i++){
        for(rand_pos = rand() % LETTER_LENGTH; letters[rand_pos] != target_pattern[i]+1; rand_pos++){
            printf("\r");
            for(finded_index=0; finded_index < i; finded_index++){
                printf("%c", target_pattern[finded_index]);
            }
            
            printf("%c", letters[rand_pos]);
            if(rand_pos > LETTER_LENGTH-1) rand_pos %= LETTER_LENGTH;

            rand_pos2 = rand() % LETTER_LENGTH;
            for(finded_index; finded_index+1 < target_pattern_length; finded_index++){
                printf("%c", letters[rand_pos2++]);
            }

            printf("\t");

            Sleep(DELAY);
        }
    }
    printf("\n\n");
    Sleep(DELAY);
}


void just_random(char *letters, int len, int lines, int delay_time_range){
    int i, j, k;
    srand((unsigned)time(NULL));

    for(i=0; i<len*2; i++){
        // printf("\r");
        printf("\e[1;1H\e[2J");
        for(j=0; j<lines; j++){
            for(k=0; k<len; k++){
                printf("%c", letters[rand() % LETTER_LENGTH]);
                Sleep(rand() % delay_time_range);
            }
            printf("\n");
        }
        // printf("\t");
        
    }
}


int main(){
    int i, length, running_index, finded_index;
    char letters[LETTER_LENGTH], characters[LETTER_LENGTH];
    char target_pattern[TARGET_PATTERN_LENGTH];

    // initialize the letters from A~Z and a~z
    create_letter_array(characters);

    // initialize the letters from all ascii printable characters
    create_ascii_printable_character(letters);


    // for(i=0; i< sizeof(letters)/sizeof(char); i++){
    //     printf("%c ", letters[i]);
    // }


    // input the target string
    if(0){  // change to 1 to run the code inside if
        printf("Enter the string you want to show: ");
        fgets(target_pattern, 99, stdin);


        // display_only_finded(target_pattern, letters);

        // display_all_cols(target_pattern, letters);

        // display_random_position(target_pattern, letters);
    }
    // just_random(letters, 80, 20);
    just_random(letters, 148, 32, 30);
    

    return 0;
}