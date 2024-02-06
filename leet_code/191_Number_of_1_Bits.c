#include <stdio.h>
#include <stdint.h>

int hammingWeight(uint32_t n) {
    int i=0;
    for(; n>0;){
        if(n&1 != 0){
            i++;
        }
        n = n>>1;
    }
    printf("%d", i);
    // return i;
}

int my_original_code(uint32_t n){
    int i=0;
    for(; n>0;){
        // printf("%u ", n);
        if(n%2 != 0){
            i++;
        }
        n = n>>3;
    }
    // printf("%d", i);

    return i;
}



int main(){
    hammingWeight(00000000000000000000000000001011);  printf("\n");
    
    hammingWeight(00000000000000000000000010000000);  printf("\n");

    hammingWeight(11111111111111111111111111111101);
    return 0;
}