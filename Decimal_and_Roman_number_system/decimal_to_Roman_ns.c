#include <stdio.h>
#include <string.h>


int main(){
    /* I=1, V=5, X=10, L=50, C=100, D=500, M=1000 */

    const char digits[10][5]={"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    const char tens_digits[10][5]={"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const char hundreds_digits[10][5] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const char thousands_digits[10][5] = {"", "M", "MM", "MMM"};

    printf("This program turns decimal positive integer number into Roman number system representation\n");
    printf("Symbols: I=1, V=5, X=10, L=50, C=100, D=500, M=1000\n");
    printf("HINT: -1 to quit the program\n");
    printf("Range: 1~3999");

    while (1){
        fflush(stdin);  /* 因為輸入小數或文字會變成無窮迴圈，最後在網路上找資料，我覺得可能是scanf造成的，緩衝區buffer的原因
                        所以加了這一行清空buffer */

        int num;
        int remaining, counter=0;
        char result[4][5]={0};

        printf("\nEnter a number:");
        scanf("%d", &num);

        if (num==-1){
            break;
        }
        else if(num<1 || num>3999){
            printf("Out of range!! Enter again!");
            continue;
        }

        while ((num/10 >= 0 || num%10 != 0) && counter<=4){
            remaining = num%10;
            num = num/10;
            counter+=1;

            if (counter==1){
                strcpy(result[3], digits[remaining]);
            }
            if (counter==2){
                strcpy(result[2], tens_digits[remaining]);
            }
            if (counter==3){
                strcpy(result[1], hundreds_digits[remaining]);
            }
            if (counter==4){
                strcpy(result[0], thousands_digits[remaining]);
            }
        }

        for (int i=0; i<=3; i++){
            if (result[i]==0){
                continue;
            }
            else{
                printf("%s", result[i]);
            }
        }

    }
    return 0;
}
