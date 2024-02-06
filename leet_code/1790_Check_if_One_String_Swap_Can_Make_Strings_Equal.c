#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areAlmostEqual(char * s1, char * s2){
    int i, count=0, f=-1, s=-1;
    for(i=0; i<strlen(s1); i++){
        if(s1[i]!=s2[i]){
            count++;
            if(count>2) return false;
            // if(count==1) f=i;
            // if(count==2) s=i;
            (count-1) ? (f=i) : (s=i);
        }
    }
    if(count!=2 && count!=0) return false;
    if(f!=-1 && s!=-1 && (s1[f]!=s2[s] || s1[s]!=s2[f])) return false;
    return true;
}

int main(){
    char s1[]="bank";
    char s2[]="kanb";
    printf("True or False(0/1): %d", areAlmostEqual(s1, s2));
}