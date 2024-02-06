#include <stdio.h>
#include <stdlib.h>

int nearestValidPoint(int x, int y, int** points, int pointsSize, int* pointsColSize){
    
    //printf("%d", *pointsColSize);    pointsSize: row size, pointsColSize: column size

    int i, j, small_index=-1, manhattan_dis, small_manhattan_dis=999999;
    for(i=0; i<pointsSize; i++){
        if(points[i][0]==x || points[i][1]==y){
            manhattan_dis = abs(points[i][0] - x) + abs(points[i][1] - y);
            if(manhattan_dis < small_manhattan_dis){
                small_manhattan_dis = manhattan_dis;
                small_index = i;
            }
            else if(manhattan_dis == small_manhattan_dis){
                if(small_index > i){
                    small_index = i;
                }
            }
        }
    }
    return small_index;
}

int main(){
    int points[][2] = {{1,2},{3,1},{2,4},{2,3},{4,4}};
    nearestValidPoint(3, 4, &points[0][0], sizeof(points)/sizeof(*points), sizeof(*points)/sizeof(int));
    //how to pass arguments in this function?
    
    // printf("%d\n", sizeof(points)/sizeof(*points));
    // printf("%d\n", sizeof(*points)/sizeof(int));
    // printf("%d", sizeof(points));

    return 0;
}