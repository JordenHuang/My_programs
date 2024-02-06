#include <stdio.h>
#include <stdbool.h>

bool isHappy(int n){
    int counter=0, sum;
    while(counter<50){
        sum=0;
        while(n!=0){
            sum += (n%10)*(n%10);
            n = n/10;
        }
        if(sum==1) return true;
        n = sum;
        counter++;
    }
    return false;
}

int main(){
    printf("True or False(0/1): %d\n", isHappy(19));
    printf("True or False(0/1): %d\n", isHappy(7));
    printf("True or False(0/1): %d\n", isHappy(3));
    printf("True or False(0/1): %d\n", isHappy(2));
    printf("True or False(0/1): %d\n", isHappy(89));
}