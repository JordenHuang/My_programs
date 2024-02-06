#include <stdio.h>

double average(int* salary, int salarySize){
    int min=salary[0], max=salary[0];
    int i, j;
    double avg=0;
    for(i=0; i<salarySize; i++){
        if(salary[i]<min) min = salary[i];
        if(salary[i]>max) max = salary[i];
        avg += salary[i];
    }
    avg -= min + max;
    avg /= salarySize-2;

    return avg;
}

int main(){
    int salary[] = {4000,3000,1000,2000};
    printf("The average: %lf", average(salary, sizeof(salary)/sizeof(int)));
    return 0;
}