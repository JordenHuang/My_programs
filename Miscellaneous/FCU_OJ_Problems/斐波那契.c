#include <stdio.h>

int main(void){
    int N, f1, f2, fn, counter, times=1;
    int input;

    scanf("%d", &N);
    while (times<=N){
        scanf("%d", &input);
        times++;

        fn=0;
        f1=0;
        f2=1;
        counter=1;
        while (counter<input){
            fn=f1+f2;
            f1=f2;
            f2=fn;
            counter++;
        }
        printf("%d\n", fn);
    }
    
    return 0;
}