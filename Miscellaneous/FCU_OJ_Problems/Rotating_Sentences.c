#include <stdio.h>
#include <string.h>

int main(void){
    char str_m[100][100];
    int i=0, j=0, k, max=0;

    for(i; i<100; i++){
        for(j; j<100; j++){
            str_m[i][j]='1';
        }
    }

    i=0;
    j=0;

    while (1){
        scanf("%c", &str_m[i][j]);
        if (str_m[i][j]=='\t'){
            str_m[i][j]='\0';
            break;
        }
        else if(str_m[i][j]=='\n'){
            if(strlen(str_m[i])>max){
                max=j;
            }

            str_m[i][j]='1';
            i++;
            j=0;
        }
        else{
            j++;
        }
    }
    
    for(j=0; j<max; j++){
        for(k=i; k>=0; k--){
            if(str_m[k][i]=='1'){
                printf("1");
            }
            else{
                printf("%c", str_m[k][j]);
            }
        }
        printf("\n");
        k=i;
    }

}


/*
    while (1){
        c=getchar();
        if (c=='\t'){
            break;
        }
        else if (c=='\n'){
            str_m[i][j]=c;
            i++;
        }
        else{
            str_m[i][j]=c;
            j++;
        }
    }

    for(i=0; i<100; i++){
        for(j=0; j<100; j++){
            printf("%c", str_m[i][j]);
        }
    }
*/
