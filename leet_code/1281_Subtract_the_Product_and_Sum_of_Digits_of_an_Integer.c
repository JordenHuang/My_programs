#include <stdio.h>

int subtractProductAndSum(int n){
    int product_of_digits=1, sum_of_digits=0, result;
    while(n>0){
        sum_of_digits += n%10;
        product_of_digits *= n%10;
        n /= 10;
    }
    result = product_of_digits - sum_of_digits;

    return result;
}

int main(){
    printf("%d", subtractProductAndSum(234));
}