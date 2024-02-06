#include <stdio.h>

int calc(int a, int b){
    if (b==1){
        return a;
    }
    else{
        return a + calc(a, b-1);
    }
}