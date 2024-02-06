#include <stdio.h>
#include <string.h>

int main(){
    char str[100]={0};
    int i=0, j, times;

    printf("Enter the string: ");
    while (1){
        scanf("%c", &str[i]);
        if(str[i]=='\n'){
            break;
        }
        i++;
    }

    // for(i=0; i<strlen(str); i++){
    //     printf("%c", str[i]);
    // }

    for(i=0; i<strlen(str)-1; i++){
        times=1;
        for(j=i+1; j<strlen(str); j++){
            if(str[i]==' '){
                continue;
            }
            else if(str[i]==str[j]){
                times++;
                str[j]=' ';
            }
        }
        if(times>1){
            printf("'%c' occur %d times\n", str[i], times);
        }
    }
    

    return 0;
}