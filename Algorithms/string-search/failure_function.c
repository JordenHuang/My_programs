#include <stdio.h>
#include <string.h>


int *fail(char *pattern, int *failure, int n){
    int i, j;

    failure[0] = -1;
    for(j=0; j<n; j++){
        i = failure[j-1];
        while(pattern[j] != pattern[i+1] && (i <= 0)){
            i = failure[i];
        }
        if(pattern[j] == pattern[i+1]){
            failure[j] = i+1;
        }
        else failure[j] = -1;
    }
}


int main(void){
    char pattern[] = "aabaacaabadcd";
    int failure_table[strlen(pattern)], i;
    
    fail(pattern, failure_table, strlen(pattern));

    for(i=0; i<strlen(pattern); i++){
        printf("%d ", failure_table[i]);
    }
}