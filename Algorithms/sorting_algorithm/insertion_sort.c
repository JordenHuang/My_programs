#include <stdio.h>

#define SIZE 5

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int nums[]){
    int i, j, target;

    // insertion sort
    for(i=0; i<SIZE-1; i++){
        target = nums[i+1];
        j=i;
        while(j >= 0 && target < nums[j]){
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = target;
    }
}

int main(){
    int i, j, min_position;
    int nums[SIZE]={5, 2, 4, 3, 1};

    printf("The array before sorting: \n");
    // printf(">");
    for(i=0; i<SIZE; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");


    insertion_sort(nums);


    printf("The result after sorting: \n");
    // printf(">");
    for(i=0; i<SIZE; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}