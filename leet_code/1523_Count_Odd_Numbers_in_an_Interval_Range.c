#include <stdio.h>

int countOdds(int low, int high){
    int count;
    if(low%2 == 0 && high%2 == 0) count = (high-low)/2; //both even
    else count = (high-low)/2 + 1;  // both odd or one of them is odd
    return count;
}


/* ÂÂ·Qªk
int count=0, mid;
    for(low, high; low<=high; low++, high--){
        if(low%2 != 0) count++;
        if(high%2 != 0) count++;
    }
    mid = low+high;
    if(mid%2==0 && (mid/2)%2 != 0) count--;//because after running the two if statement above,
                                           //the same number will be counted twice, so it needs to minus 1
    return count;
*/


int main(){
    printf("%d", countOdds(3, 7));
    return 0;
}