#include <stdio.h>

unsigned int power(int base, int exponent){
    if (exponent==0){
        return 1;
    }

    else {
        return base * power(base, exponent-1);
    }
}