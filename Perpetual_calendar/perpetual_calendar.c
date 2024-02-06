#include <stdio.h>

int check_validity(int ad, int month);
int check_leap_year(int ad);
int count_point_day(int ad);
int print_months(int point_day, int week_day, int is_leap_year, int specific_month);


int main(void){
    int ad, month, is_leap_year, week_day_of_point_day;

    printf("This program is a perpetual calendar");
    printf("\nHINT: AD=�褸, AD year = '0' to quit");
    while (1){
        fflush(stdin);
        printf("\nEnter an AD year: ");
        scanf("%d", &ad);
        if (ad==0){
            printf("Quit");
            break;
        }
        printf("Enter a month of that year (If not, enter '0'): ");
        scanf("%d", &month);

        if (check_validity(ad, month)==0){
            continue;
        }

        is_leap_year=check_leap_year(ad);
        //printf("%d\n", is_leap_year);

        week_day_of_point_day=count_point_day(ad);
        //printf("%d\n", week_day_of_point_day);

        if (month==0){
            printf("%d�~���~��:\n", ad);
            print_months(9, week_day_of_point_day, is_leap_year, month);
        }
        else{
            printf("%d�~%2d�몺���:\n", ad, month);
            print_months(9, week_day_of_point_day, is_leap_year, month);
        }

        
    }
    return 0;
}

int check_validity(int ad, int month){  //�P�_�ϥΪ̿�J�O�_�X�k���{��
    if (ad<0){
        printf("Invalid AD year!\n");
        return 0;
    }
    if (month<0 || month>12){
        printf("Invalid month!\n");
        return 0;
    }
    
    return 1;
}

int check_leap_year(int ad){    //�P�_�O���O�|�~���{��
    // If it's leap, returns 1, else returns 0
    if (ad%4==0 && ad%100!=0){
        return 1;
    }
    else if (ad%400==0){
        return 1;
    }
    else{
        return 0;
    }
}

int count_point_day(int ad){
    //���:2000�~���P�M��(�G��̫�@��)���P���G
    int point_year=2000, week_day_of_point_day=2;

    ad=ad-1;    // ��X�e�@�~���P�M�骺�P��,�Ӥ��~��1/9���P���P���ۦP

    if (ad<point_year){     //�p�G�~���b2000�e
        while (point_year>ad){
            if (check_leap_year(point_year)){
                week_day_of_point_day-=2;
                point_year-=1;
            }
            else{
                week_day_of_point_day-=1;
                point_year-=1;
            }
        }
    }
    else if (ad>point_year){    //�p�G�~���b2000��
        while (point_year<ad){
            if (check_leap_year(point_year+1)){ // +1����]�O�쨺�@�~,�Ӥ��O2000�}�l,�O2001�}�l
                week_day_of_point_day+=2;
                point_year+=1;
            }
            else{
                week_day_of_point_day+=1;
                point_year+=1;
            }
        }
    }

    while (week_day_of_point_day<0){    //�N�P���ƾ�z�b0~6
        week_day_of_point_day+=7;
    }
    while (week_day_of_point_day>6){    //�N�P���ƾ�z�b0~6
        week_day_of_point_day-=7;
    }

    return week_day_of_point_day;
}


int print_months(int point_day, int week_day, int is_leap_year, int specific_month){
    char months[13][10]={"", "January", "February", "March", "April", "May" , "June", "July", "August", "September"
                        , "October", "November", "December"};
    int days_in_a_month[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int a_year[72][7]={0};

    //�|�~��2�릳29��
    if (is_leap_year){
        days_in_a_month[2]=29;
    }

    //�Nweek_day�Mpoint_day�ܦ��Ӥ몺1��
    week_day=week_day-((point_day-1)%7);
    point_day=1;
    if (week_day<0){
        week_day=week_day+7;
    }

    //�N��~��������x�s��G���}�C��
    for (int m=1; m<=12; m++){
        for (int row=6*(m-1); row<=5+6*(m-1); row++){
            for (; week_day<=6 && point_day<=days_in_a_month[m]; week_day++, point_day++){
                a_year[row][week_day]=point_day;
            }
            if (week_day>6){
                week_day=0;
            }
        }
        point_day=1;
    }

    if (specific_month==0){     //�L��~���~�䪺�{��
        for (int m=1; m<=12; m+=3){
            printf("%27s    %27s    %27s\n", months[m], months[m+1], months[m+2]);
            printf("SUN MON TUE WED THU FRI SAT    SUN MON TUE WED THU FRI SAT    SUN MON TUE WED THU FRI SAT\n");
            for (int i=6*(m-1); i<=5+6*(m-1); i++){
                for (int j=0; j<=6; j++){
                    if (a_year[i][j]==0){
                        printf("    ");
                    }
                    else{
                        printf(" %2d ", a_year[i][j]);
                    }
                }
                printf("   ");
                for (int j=0; j<=6; j++){
                    if (a_year[i+6][j]==0){
                        printf("    ");
                    }
                    else{
                        printf(" %2d ", a_year[i+6][j]);
                    }
                }
                printf("   ");
                for (int j=0; j<=6; j++){
                    if (a_year[i+12][j]==0){
                        printf("    ");
                    }
                    else{
                        printf(" %2d ", a_year[i+12][j]);
                    }
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    else{       //�L�S�w������{��
        printf("%27s \n", months[specific_month]);
        printf("SUN MON TUE WED THU FRI SAT\n");
        for (int i=6*(specific_month-1); i<=5+6*(specific_month-1); i++){
            for (int j=0; j<=6; j++){
                if (a_year[i][j]==0){
                    printf("    ");
                }
                else{
                    printf(" %2d ", a_year[i][j]);
                }
            }
            printf("\n");
        }
    }
}


/* �ǲߤ�x:
2022/11/09  1.�}�l�s�@�U�~��:��J�褸�~,��X��~�����;��J�褸�~���,��X���Ӥ몺���(�H�U������ʬ���)
            2.��Ǥ�:2000/2/29���P���G,4/4,6/6,8/8,10/10,12/12,5/9,9/5,7/11,11/7���P�����P��Ǥ�ۦP
            3.�C100�~����Ǥ�P���ƫ��H�U�W��:�P���G�B�P����B�P�����B�P���T
            4.�C�L�@�ӥ��~,��Ǥ骺�P���ƥ[1,�C�L�@�Ӷ|�~,��Ǥ�P���ƥ[2;�C�L12�~,��Ǥ骺�P���ƥ[1

2022/11/11  1.�Q�z�L�N��������P�����覡,�s�@�@�ӰƵ{��,�άP���ӲզX����;  �o�ӷQ�k��ӧﱼ�F 

2022/11/12  1.�s�@�X��L�X�@�Ӥ��䪺�Ƶ{��,�ѼƬO ����B����B�P��;  ��Ӥ]�ﱼ,�]���o�˨S��k�H �T�Ӥ묰�@�C �L�X�� 

2022/11/13  1.�P�M��k�h,�p��X�h�~2�몺�̫�@��(�P�M��)���P���X,�h���~��1/9���P���]�|�@��
            2.���:2000�~���P�M�鬰�P���G,�C�L12�~���P�M��P���ƥ[1 (2022/11/09��4.)
            3.�s�@�p��h�~�P�M�骺�{��,�ĥX���~1/9���P��,�̫�L�X���~���~��
*/
