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



/* �ǲߤ�x:
2022/11/03  1.�W���ǲߨ�scanf����h�Ϊk,�Ҧp����i��J����r,�H�Ψ��Ϊ��r��;
            2.�ǲ�<ctype.h>�M<string.h>�зǨ禡�w�̪�isdigit()�Bisupper()�Bstrlen()���P�_�r���H�Ϊ��ת�function

2022/11/05  1.�ǲ�<ctype.h>����ispunct(),�ΨӧP�_�O�_�����I�Ÿ�,���M���S�Ψ�
            2.�ڵo�{�bnested for loop�̪�continue�u�|�^��W�@��for,���|��̥~����for
            3.�����P�_user input�����e�O ���Ʀr �� �����T��ù���Ʀr���Ƶ{��; �����b�Y�O��J0000�h�n�p��B�z

2022/11/06  1.�ǲ�<math.h>�̪�atoi()
            2.�ϥΤ��e�������{��,����decimal to Roman number������
            3.�n�qù���Ʀr�ഫ���̶i��,�ڪ��Q�k�O�q�w�����̶i����ù���Ʀr�o�X�����G�ӳv�@���,�������@�˪�,
              �M���X�w�����̶i�쵲�G,���]���d�b'�̶i����ù���Ʀr'�o�ӰƵ{���O������X,�S���^�ǭ�,�ɭP�ڵL�k�~��U�h;

2022/11/07  1.�Q��k��'�̶i����ù���Ʀr'�o�ӰƵ{����^���ഫ�᪺���G,�Ӥ��O������X,�]���W����F'�禡�^�ǰ}�C'�����,
              �ڥΪ���k�O�ǤJ�D�{�����}�C����}��Ƶ{��,�Ƶ{���ઽ�����ܳo�Ӱ}�C�����e,�ڬO��strcat�Ӭ۱��r��,���M���\
              ����X,���}�C���٦��e�@�������e,�]���ϥΤFmemset�ӲM�Ű}�C���e
            2.��ӷQ�Q,���Ӧb'�̶i����ù���Ʀr'�o�ӰƵ{���̫ŧi�@��static���}�C,�̫�^�ǥL����}

2022/11/09  1.'�̶i����ù���Ʀr'�o�ӰƵ{���̫ŧi�@��static���}�C,�̫�^�ǥL����}-->����
            2.�s�@'ù���Ʀr��̶i��'���Ƶ{��
            3.�����F!
            4.�o�{�r����׳̤j�ȳ]��,����15,�@�}�l�u�Q��888��ù���Ʀr���׬�12,�����F3888�o�Ӫ��ק�����Ʀr
            5.�w�ץ�

*/



/* �ڵo�{�bnested for loop�̪�continue�u�|�^��W�@��for,���|��̥~����for
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
