#include <stdio.h>

int arraySign(int* nums, int numsSize){
    int i, pos_or_neg=1;
    for(i=0; i<numsSize; i++){
        if(nums[i]==0){
            return 0;
        }
        else if(nums[i] < 0){
            pos_or_neg *= -1;
        }
    }
    return pos_or_neg; 
}

int main(){
    int nums_1[] = {-1,-2,-3,-4,3,2,1};  // return 1
    int nums_2[] = {1,5,0,2,-3};  // return 0
    int nums_3[] = {-1,1,-1,1,-1};  // return -1

    printf("%d\n", arraySign(nums_1, sizeof(nums_1)/sizeof(int)));
    printf("%d\n", arraySign(nums_2, sizeof(nums_1)/sizeof(int)));
    printf("%d\n", arraySign(nums_3, sizeof(nums_1)/sizeof(int)));

    return 0;
}