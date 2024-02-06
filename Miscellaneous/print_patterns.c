#include <stdio.h>

int r, c, m=0;

void pattern1(int n);
void pattern2(int n);
void pattern3(int n);
void pattern4(int n);
void pattern5(int n);
void pattern6(int n);
void pattern7(int n);
void pattern8(int n);
void pattern9(int n);
void pattern10(int n);
void pattern11(int n);
void pattern12(int n);
void pattern13(int n);
void pattern14(int n);
void pattern15(int n);
void pattern16(int n);


int main(void){
    int p_t,n;
    printf("Enter pattern number: ");
    scanf("%d", &p_t);
    printf("Enter a number n: ");
    scanf("%d", &n);

    switch (p_t){
        case 1:
            pattern1(n);
            break;
        case 2:
            pattern2(n);
            break;
        case 3:
            pattern3(n);
            break;
        case 4:
            pattern4(n);
            break;
        case 5:
            pattern5(n);
            break;
        case 6:
            pattern6(n);
            break;
        case 7:
            pattern7(n);
            break;
        case 8:
            pattern8(n);
            break;
        case 9:
            pattern9(n);
            break;
        case 10:
            pattern10(n);
            break;
        case 11:
            pattern11(n);
            break;
        case 12:
            pattern12(n);
            break;
        case 13:
            pattern13(n);
            break;
        case 14:
            pattern14(n);
            break;
        case 15:
            pattern15(n);
            break;
        case 16:
            pattern16(n);
            break;
        default:
            printf("Invalid pattern number");
            break;
    }

    return 0;
}

void pattern1(int n){
    //int r, c;
    for (r=1; r<=n; r++){
        for (c=1; c<=n; c++){
            printf("*");
        }
        printf("\n");
    }
}
void pattern2(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=r; c++){
            printf("*");
        }
        printf("\n");
    }
}
void pattern3(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=(n-r+1); c++){
            printf("*");
        }
        printf("\n");
    }
}
void pattern4(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=r; c++){
            printf("%d ", c);
        }
        printf("\n");
    }
}
void pattern5(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=r; c++){
            printf("*");
        }
        printf("\n");
    }
    for (r=1; r<=n-1; r++){
        for (c=1; c<=n-r; c++){
            printf("*");
        }
        printf("\n");
    }
}
void pattern6(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=n; c++){
            if (c<=n-r)
                printf(" ");
            else{
                printf("*");
            }
        }
        printf("\n");
    }
}
void pattern7(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=n; c++){
            if (c<=r-1)
                printf(" ");
            else{
                printf("*");
            }
        }
        printf("\n");
    }
}
void pattern8(int n){
    for (r=1; r<=n; r++){
        for (c=1, m=r-1; c<=n*2-1; c++){
            if (c>=n-m && c<=n+m)
                printf("*");
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
void pattern9(int n){
    for (r=1; r<=n; r++){
        for (c=1, m=n-r; c<=n*2-1; c++){
            if (c>=n-m && c<=n+m)
                printf("*");
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
void pattern10(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=n; c++){
            if (c<=n-r){
                printf(" ");
            }
            else{
                printf("* ");
            }
        }
        printf("\n");
    }
}
void pattern11(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=n; c++){
            if (c<=r-1)
                printf(" ");
            else{
                printf("* ");
            }
        }
        printf("\n");
    }
}
void pattern12(int n){
    for (r=1; r<=n; r++){
        for (c=1; c<=n; c++){
            if (c<=r-1)
                printf(" ");
            else{
                printf("* ");
            }
        }
        printf("\n");
    }
    for (r=1; r<=n; r++){
        for (c=1; c<=n; c++){
            if (c<=n-r){
                printf(" ");
            }
            else{
                printf("* ");
            }
        }
        printf("\n");
    }
}
void pattern13(int n){
    for (r=1; r<=n; r++){
        for (c=1, m=r-1; c<=n*2-1; c++){
            if (c==n-m || c==n+m)
                printf("*");
            else if (r==n){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
void pattern14(int n){
    for (r=1; r<=n; r++){
        for (c=1, m=n-r; c<=n*2-1; c++){
            if (c==n-m || c==n+m)
                printf("*");
            else if (r==1){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
void pattern15(int n){
    for (r=1; r<=n; r++){
        for (c=1, m=r-1; c<=n*2-1; c++){
            if (c==n-m || c==n+m)
                printf("*");
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    for (r=n+1, m=n-2; r<=n*2-1; r++, m--){
        for (c=1; c<=n*2-1; c++){
            if (c==n-m || c==n+m)
                printf("*");
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
void pattern16(int n){
    for (r=1; r<=n; r++){
        int num=1;  // 第n+1列的值是C n 取 (col)
        int i=1, tr=r-1;
        for (c=1; c<=n; c++){
            if (c<=n-r){
                printf("   ");
            }
            else if (r>2 && i<=tr){
                printf("%6d", num);
                num = num * (tr-i+1)/i;
                i++;
            }
            else{
                printf("%6d", 1);
            }
        }
        printf("\n");
    }
}