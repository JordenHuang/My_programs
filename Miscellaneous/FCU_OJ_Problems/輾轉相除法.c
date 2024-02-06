#include <stdio.h>

unsigned long long gcd(unsigned long long a, unsigned long long b);

int main(void){
    int num, t=0;
    unsigned long long a, b;
    unsigned long long gcd_num, lcm_num;

    scanf("%d", &num);
    while (t<num){
        scanf("%llu%llu", &a, &b);

        gcd_num = gcd(a, b);
        lcm_num = a*b/gcd_num;
        
        printf("%llu\n", lcm_num);
        t++;
    }

    return 0;
}

unsigned long long gcd(unsigned long long a, unsigned long long b){
	if (b==0){
        return a;
    }
    else{
        return gcd(b, a%b);
    }
}
