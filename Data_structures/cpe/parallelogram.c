#include <stdio.h>

/*
0.000 0.000 0.000 1.000 0.000 1.000 1.000 1.000
1.000 0.000 3.500 3.500 3.500 3.500 0.000 1.000
*/

typedef struct coor{
    double x;
    double y;
}coor;

int main(){
    coor coors[4], two[2];
    coor same, result;
    int i, j, flag=0;

    while(scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &coors[0].x, &coors[0].y, &coors[1].x, &coors[1].y, &coors[2].x, &coors[2].y, &coors[3].x, &coors[3].y) != EOF){
        /*for(i=1; i<4; i++){
            scanf("%lf %lf ", &coors[i].x, &coors[i].y);
        }*/
        flag = 0;
        for(i=0; i<4-1; i++){
            for(j=i+1; j<4; j++){
                if(coors[i].x == coors[j].x && coors[i].y == coors[j].y){
                    same = coors[j];
                    flag = 1;
                }
            }
            if(flag) break;
        }
        for(i=0; i<4; i++){
            printf("%lf %lf %lf %lf %lf %lf %lf %lf\n", coors[0].x, coors[0].y, coors[1].x, coors[1].y, coors[2].x, coors[2].y, coors[3].x, coors[3].y);
            printf("same: %lf %lf\n", same.x, same.y);
        }
        
        for(i=0, j=0; (i<4) && (j<2); i++){
            // FIXME: when coors = (2, 1) and same = (2, 1), it will not store into the two array
            // that's why the output is so weird
            // sample input: 8 4 2 1 2 1 2 1
            if((coors[i].x != same.x) || (coors[i].y != same.y)){
            	two[j].x = coors[i].x;
                two[j].y = coors[i].y;
                j++;
                // printf("%lf %lf %lf %lf \n",  two[0].x, two[0].y, two[1].x, two[1].y);
            }
        }
printf("%lf %lf %lf %lf \n",  two[0].x, two[0].y, two[1].x, two[1].y);
        //result.x = (two[0].x * 2 - same.x + two[1].x * 2 - same.x)/2;
        //result.y = (two[0].y * 2 - same.y + two[1].y * 2 - same.y)/2;
		// result.x = same.x + (two[0].x - same.x) + (two[1].x - same.x);
		// result.y = same.y + (two[0].y - same.y) + (two[1].y - same.y);
        result.x = two[0].x + two[1].x - same.x;
        result.y = two[0].y + two[1].y - same.y;
		
        printf("%.3lf %.3lf\n", result.x, result.y);
    }

    return 0;
}