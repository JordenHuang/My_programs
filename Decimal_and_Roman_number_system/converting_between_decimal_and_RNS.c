#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int check_all_digit_and_validity(char user_input[]);
int check_all_rns(char user_input[]);
char *decimal_to_rns(int num);
int rns_to_decimal(char user_input[]);

int main(void){
    unsigned char user_input[16];
    int is_digits, is_rns;
    int num;

    printf("This program converts between decimal numbers and Roman numbers");
    printf("\nI=1, V=5, X=10, L=50, C=100, D=500, M=1000");
    printf("\nHINT: Only 'Positive decimal integer number(1~3999)' or 'Capital Roman number' !");

    while (1){
        fflush(stdin);
        printf("\nEnter a decimal number or a Roman number (0 to exit): ");
        scanf("%15s", user_input);

        printf("The user input is: %s\n", user_input);
        //printf("\nstring len: %d\n", strlen(user_input));

        is_digits = check_all_digit_and_validity(user_input);
        is_rns = check_all_rns(user_input);
        //printf("digits:%d, RNS:%d", is_digits, is_RNS);

        // check user input is valid or not
        if (strlen(user_input)==1 && user_input[0]=='0'){
            printf("Exit");
            break;
        }
        else if (is_digits == is_rns){
            printf("Invalid input!\n");
            continue;
        }

        if (is_digits){
            num = atoi(user_input);
            if (num>3999 || num<1){
                printf("Out of range!\n");
                continue;
            }
            printf("The result is: %s", decimal_to_rns(num));
        }
        if (is_rns){
            num = rns_to_decimal(user_input);
            if (num==0){
                printf("Incorrect Roman number!");
            }
            else{
                printf("The result is: %d", num);
            }
        }
        printf("\n");
    }
    
    return 0;
}


int check_all_digit_and_validity(char user_input[]){
    // check all are digits or not
    for (int index=0; index<strlen(user_input); index++){    
        if (isdigit(user_input[index])){
            continue;
        }
        else{
            return 0;
        }
    }
    // now it's all digit, then check if strlen is less than 4, because the number must less than 3999 
    if (strlen(user_input)>4){
        return 0;
    }
    // if user input 0000 or 000 or 00, it will report invalid input
    else if (atoi(user_input)==0){
        return 0;
    }
    return 1;
}

int check_all_rns(char user_input[]){
    const char RNS[]={'I', 'V', 'X', 'L', 'C', 'D', 'M'};

    for (int index=0; index<strlen(user_input); index++){
        //printf("index:%d ", index);
        for (int RNS_index=0, valid=0; RNS_index<=6; RNS_index++){
            //printf("RNS_index:%d ", RNS_index);
            if (user_input[index]==RNS[RNS_index]){
                valid+=1;
            }
            else if (RNS_index==6 && valid==0){
                return 0;
            }
        }
    }
    return 1;
}

char *decimal_to_rns(int num){
    const char digits[10][5]={"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    const char tens_digits[10][5]={"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const char hundreds_digits[10][5] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const char thousands_digits[10][5] = {"", "M", "MM", "MMM"};

    int remaining, counter=0;
    char result[4][5]={0};
    static char final_result[15];
    memset(final_result, 0, 15);

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
            strcat(final_result, result[i]);
        }
    }
    //printf("%s", final_result);
    return final_result;
}

int rns_to_decimal(char user_input[]){
    switch (user_input[0]){
        case 'I':
            for (int num=1; num<=9; num++){
                if (strcmp(user_input, decimal_to_rns(num))==0){
                    return num;
                }
            }
            break;

        case 'V':
            for (int num=5; num<=8; num++){
                if (strcmp(user_input, decimal_to_rns(num))==0){
                    return num;
                }
            }
            break;

        case 'X':
            for (int num=10; num<=99; num++){
                if (strcmp(user_input, decimal_to_rns(num))==0){
                    return num;
                }
            }
            break;
        
        case 'L':
            for (int num=50; num<=89; num++){
                if (strcmp(user_input, decimal_to_rns(num))==0){
                    return num;
                }
            }
            break;
        
        case 'C':
            for (int num=100; num<=999; num++){
                if (strcmp(user_input, decimal_to_rns(num))==0){
                    return num;
                }
            }
            break;
        
        case 'D':
            for (int num=500; num<=899; num++){
                if (strcmp(user_input, decimal_to_rns(num))==0){
                    return num;
                }
            }
            break;
        
        case 'M':
            for (int num=1000; num<=3999; num++){
                if (strcmp(user_input, decimal_to_rns(num))==0){
                    return num;
                }
            }
            break;
        
        default:
            //return 0;
            break;
    }
    return 0;
}



/* 學習日誌:
2022/11/03  1.上網學習到scanf的更多用法,例如限制可輸入的文字,以及取用的字數;
            2.學習<ctype.h>和<string.h>標準函式庫裡的isdigit()、isupper()、strlen()等判斷字元以及長度的function

2022/11/05  1.學習<ctype.h>中的ispunct(),用來判斷是否為標點符號,雖然說沒用到
            2.我發現在nested for loop裡的continue只會回到上一個for,不會到最外面的for
            3.完成判斷user input的內容是 全數字 或 全正確的羅馬數字的副程式; 結束在若是輸入0000則要如何處理

2022/11/06  1.學習<math.h>裡的atoi()
            2.使用之前完成的程式,完成decimal to Roman number的部分
            3.要從羅馬數字轉換成十進位,我的想法是從已知的十進位轉羅馬數字得出的結果來逐一比對,直到比對到一樣的,
              然後輸出已知的十進位結果,但因為卡在'十進位轉羅馬數字'這個副程式是直接輸出,沒有回傳值,導致我無法繼續下去;

2022/11/07  1.想辦法使'十進位轉羅馬數字'這個副程式能回傳轉換後的結果,而不是直接輸出,因此上網找了'函式回傳陣列'的資料,
              我用的方法是傳入主程式中陣列的位址到副程式,副程式能直接改變這個陣列的內容,我是用strcat來相接字串,雖然成功
              的輸出,但陣列裡還有前一次的內容,因此使用了memset來清空陣列內容
            2.後來想想,應該在'十進位轉羅馬數字'這個副程式裡宣告一個static的陣列,最後回傳他的位址

2022/11/09  1.'十進位轉羅馬數字'這個副程式裡宣告一個static的陣列,最後回傳他的位址-->完成
            2.製作'羅馬數字轉十進位'的副程式
            3.完成了!
            4.發現字串長度最大值設錯,應為15,一開始只想到888的羅馬數字長度為12,忽略了3888這個長度更長的數字
            5.已修正

*/



/* 我發現在nested for loop裡的continue只會回到上一個for,不會到最外面的for
int check_all_upper(char user_input[]){
    const char RNS[]={'I', 'V', 'X', 'L', 'C', 'D', 'M'};

    for (int index=0; index<strlen(user_input); index++){
        printf("index:%d ", index);
        for (int RNS_index=0, valid=0; RNS_index<=6; RNS_index++){
            printf("RNS_index:%d ", RNS_index);
            if (user_input[index]==RNS[RNS_index]){
                //valid+=1;
                continue;       //here
            }
            else if (RNS_index==6 && valid==0){
                return 0;
            }
        }
    }
    return 1;
}
*/
