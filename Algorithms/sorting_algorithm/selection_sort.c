#include <stdio.h>

#define SIZE 5

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int a[], int size_a){
    int i, j, min, min_position, temp;

    for (i=0; i<size_a-1; i++){
        min=a[i];
        for (j=i+1; j<size_a; j++){
            if (min>a[j]){
                min=a[j];
                min_position=j;
            }
        }
        if (min!=a[i]){
            temp=a[i];
            a[i]=a[min_position];
            a[min_position]=temp;
        }
        //printf("\na[i]: %d, a[min_position]:%d", a[i], a[min_position]);
    }
}

void better_selection_sort(int a[], int size_a){
    int i, j, min_position;

    for(i=0; i<size_a-1; i++){
            min_position = i;
            for(j=i+1; j<size_a; j++){
                if(a[min_position] > a[j]){
                    min_position = j;
                }
            }
            if(min_position != i){
                swap(&a[i], &a[min_position]);
            }
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


    better_selection_sort(nums, SIZE);


    printf("The result after sorting: \n");
    // printf(">");
    for(i=0; i<SIZE; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}