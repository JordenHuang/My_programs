#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int i, j, nums[SIZE];
    
    srand((unsigned)time(NULL));
    printf("The original array is: \n");
    for(i=0; i<SIZE; i++){
        nums[i] = rand() % 50 + 1;
        printf("%d ", nums[i]);
    }
    printf("\n");


    for(i=0; i<SIZE-1; i++){
        for(j=0; j+1 < SIZE-i; j++){
            if(nums[j] > nums[j+1]) swap(&nums[j], &nums[j+1]);
        }
    }


    printf("The result after sorting: \n");
    for(i=0; i<SIZE; i++){
        printf("%d ", nums[i]);
    }

    return 0;
}



/* v2
int main(){
    int n, i=0, j=0, temp, done=0;

    printf("Enter the size of element: ");
    scanf("%d", &n);
    int a[n];

    printf("Enter the elements: ");
    while(i<n){
        scanf("%d", &a[i]);
        i++;
    }

    for(j=0; j<n-1; j++){
        done=0;
        for(i=0; i<n-1; i++){
            if(a[i]>a[i+1]){
                temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
            }
            else{
                done++;
            }
        }
        if(done==n-2){
            break;
        }
    }

    for(i=0; i<n; i++){
        printf("%d ", a[i]);
    }
}
*/



/* v1
int main(void){
    int nums[10];
    int r, c, temp;

    printf("The buble sort program\nEnter 10 numbers\n");
    for (int n=1; n<=10; n++){
        printf("Enter number %d: ", n);
        scanf("%d", &nums[n-1]);
    }

    for (r=0; r<=( sizeof(nums)/sizeof(nums[0]) )-1; r++){
        for (c=0; c<=( sizeof(nums)/sizeof(nums[0]) )-1; c++){
            if (nums[r]<nums[c]){
                temp=nums[r];
                nums[r]=nums[c];
                nums[c]=temp;
            }
        }
    }

    for (int i=0; i<=( sizeof(nums)/sizeof(nums[0]) )-1; i++){
        if (i==( sizeof(nums)/sizeof(nums[0]) )-1){
            printf("%d", nums[i]);
        }
        else{
            printf("%d < ", nums[i]);
        }
    }

	return 0;
}
*/