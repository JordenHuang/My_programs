#include <stdio.h>

int gcd(int a, int b);

int main(void){
    int a, b;
    int gcd_num, lcm_num;

    scanf("%d%d", &a, &b);
    
    gcd_num = gcd(a, b);
    lcm_num = a*b/gcd_num;

    printf("%d %d", gcd_num, lcm_num);

    return 0;
}

int gcd(int a, int b){
	if (b==0){
        return a;
    }
    else{
        return gcd(b, a%b);
    }
}
