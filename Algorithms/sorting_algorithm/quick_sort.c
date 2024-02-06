#include <stdio.h>

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
        // for(int a=0; a<10; a++){
        //     printf("%d ", arr[a]);
        // }
        // printf("\n");
    }
    swap(arr, i, right);
    // for(int a=0; a<10; a++){
    //     printf("%d ", arr[a]);
    // }
    // printf("\n");

    quick_sort(arr, left, i-1);
    quick_sort(arr, i+1, right);
}

int main(){
    int arr[]={-509,-19,-439,-264,-404,-369,-299,-89,-229,-54,-194,16,-544,-159,-124,-474,-334}; //{8,6,1,10,5,3,9,2,7,4};
    int i, arr_size=sizeof(arr)/sizeof(int);
    quick_sort(arr, 0, arr_size-1);
    for(i=0; i<arr_size; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}