#include <stdio.h>
#include <string.h>


void reverse(char * s, int head, int tail){
    char temp, h, t;
    int i, j;
    for(head, tail; head<tail; head++, tail--){
        temp = s[head];
        s[head] = s[tail];
        s[tail] = temp;
    }
}

char * reverseStr(char * s, int k){
    int length_s = strlen(s);
    int t, head, tail;

    if(length_s >= k && length_s < k*2){
        head = 0;
        tail = k-1;
        reverse(s, head, tail);
    }
    else if(length_s < k*2){
        head = 0;
        tail = length_s-1;
        reverse(s, head, tail);
    }
    else{
        for(t=0; (t+1)*k <= length_s; t+=2){
            head = t*k;
            tail = (t+1)*k - 1;
            reverse(s, head, tail);
        }
        if(length_s >= t*k && length_s < (t+1)*k){
            head = t*k;
            tail = length_s - 1;
            reverse(s, head, tail);
        }
        else if((t+1)*k > length_s){
            head = (t+1)*k;
            tail = length_s-1;
            reverse(s, head, tail);
        }
    }

    printf("%s", s);
    return s;
}

int main(){
    char s[1000];
    int k;

    scanf("%s", s);
    scanf("%d", &k);
    reverseStr(s, k);

    return 0;
}