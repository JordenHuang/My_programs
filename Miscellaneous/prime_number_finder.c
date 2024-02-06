#include <stdio.h>

void prime_finder(int count){
    unsigned int finded_prime[count];
    int num=3, index=1, check=0, i;  // num:一直往後要找的數, index:下一個找到後要放的位置, check:用來判斷是否為質數的變數, i:變動的位置

    finded_prime[0]=2;
    for(num=3; index<count; num++){
        for(i=0, check=0; i<index; i++){
            if(num%finded_prime[i] == 0 && finded_prime[i] <= num/2){ // 只需判斷到那個數的一半就可以 
                check=1;
                continue;
            }
        }
        if(check==0){
            finded_prime[index]=num;
            index++;
        }
    }

    printf("The prime numbers: ");
    for(index=0; index<count; index++){
        printf("%u ", finded_prime[index]);
    }
}

int main(){
    int how_many;
    printf("Enter how many prime numbers you want to find: ");
    scanf("%d", &how_many);
    prime_finder(how_many);

    return 0;
}