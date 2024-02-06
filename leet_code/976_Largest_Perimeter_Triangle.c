#include <stdio.h>

int largestPerimeter(int* nums, int numsSize){
    int i, j, k, max=0, max_p, temp;
    for(i=0; i<numsSize; i++){
        for(j=i+1, max=0; j<numsSize; j++){
            if(nums[j]>max){
                max = nums[j];
                max_p = j;
            }
        }
        if(nums[i]<nums[max_p]){
            temp = nums[i];
            nums[i] = nums[max_p];
            nums[max_p] = temp;
        }

        if(i>=2){
            if(nums[i-2] < nums[i-1]+nums[i]) return nums[i-2]+nums[i-1]+nums[i];
        }
    }
    return 0;
}

int main(){
    int nums[] = {2,1,2};  //{1,2,1,10};
    printf("%d", largestPerimeter(nums, sizeof(nums)/sizeof(int)));
    return 0;
}