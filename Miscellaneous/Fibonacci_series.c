#include <stdio.h>

int main(){
    int N, f1=0, f2=1, fn=0, counter=0;

    printf("This program shows the Fibonacci series (starts with 0)\n");
    printf("Enter a number N to show N numbers in Fibonacci series: ");
    scanf("%d", &N);

    printf("%d, %d", f1, f2);
    while (counter<N-2){
        printf(", ");
        fn=f1+f2;
        f1=f2;
        f2=fn;
        printf("%d", fn);
        counter++;

    }
    
return 0;
}