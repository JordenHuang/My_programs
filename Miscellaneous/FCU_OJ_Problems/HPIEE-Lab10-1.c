#include <stdio.h>

unsigned long long calc(unsigned long long n){
    if (n==1){
        return 1;
    }
    else{
        return n*calc(n-1);
    }
}