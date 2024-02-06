#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j, temp;
    *returnSize=2;
    for(i=0; i<numsSize; i++){
        temp = target - nums[i];
        for(j=i+1; j<numsSize; j++){
            if (nums[j]==temp){
                int *ans = malloc(2*sizeof(int));
                ans[0] = i;
                ans[1] = j;
                return ans;
            }
        }
    }
    return 0;
}

int main(){
    int nums[] = {2,7,11,15}, target = 9;
    int numsSize = sizeof(nums)/sizeof(int);
    int returnSize;
    // printf("%d", numsSize);
    int *ans = twoSum(nums, numsSize, target, &returnSize);
    for(int i=0; i<returnSize; i++){
        printf("%d ", ans[i]);
    }
    free(ans);
    
}