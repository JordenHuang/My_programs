#include <stdio.h>
#include <stdbool.h>

void swap(int *arr, int a, int b){
    int temp;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void quick_sort(int *arr, int left, int right){
    if(left >= right) return;
    int i=left, j=right, target=arr[right];
    while(i!=j){
        while(arr[i]<=target && i<j) i++;
        while(arr[j]>=target && i<j) j--;
        if(i<j) swap(arr, i, j);
    }
    swap(arr, i, right);

    quick_sort(arr, left, i-1);
    quick_sort(arr, i+1, right);
}

bool canMakeArithmeticProgression(int* arr, int arrSize){
    int i, j, min, max, minp, maxp, dif;
    quick_sort(arr, 0, arrSize-1);
    dif = arr[1]-arr[0];
    for(i=1; i<(arrSize-1); i++){
        if((arr[i]+dif) != arr[i+1]) return false;
    }
    return true;
}

int main(){
    int arr[]={8,6,1,10,5,3,9,2,7,4};
    int i, arr_size=sizeof(arr)/sizeof(int);
    printf("True or False(0/1): %d\nThe array is: ", canMakeArithmeticProgression(arr, arr_size));
    for(i=0; i<arr_size; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}