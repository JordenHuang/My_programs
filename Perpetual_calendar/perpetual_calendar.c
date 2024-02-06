#include <stdio.h>

int check_validity(int ad, int month);
int check_leap_year(int ad);
int count_point_day(int ad);
int print_months(int point_day, int week_day, int is_leap_year, int specific_month);


int main(void){
    int ad, month, is_leap_year, week_day_of_point_day;

    printf("This program is a perpetual calendar");
    printf("\nHINT: AD=西元, AD year = '0' to quit");
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
            printf("%d年的年曆:\n", ad);
            print_months(9, week_day_of_point_day, is_leap_year, month);
        }
        else{
            printf("%d年%2d月的月曆:\n", ad, month);
            print_months(9, week_day_of_point_day, is_leap_year, month);
        }

        
    }
    return 0;
}

int check_validity(int ad, int month){  //判斷使用者輸入是否合法的程式
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

int check_leap_year(int ad){    //判斷是不是閏年的程式
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
    //基準:2000年的判決日(二月最後一天)為星期二
    int point_year=2000, week_day_of_point_day=2;

    ad=ad-1;    // 算出前一年的判決日的星期,而今年的1/9的星期與之相同

    if (ad<point_year){     //如果年份在2000前
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
    else if (ad>point_year){    //如果年份在2000後
        while (point_year<ad){
            if (check_leap_year(point_year+1)){ // +1的原因是到那一年,而不是2000開始,是2001開始
                week_day_of_point_day+=2;
                point_year+=1;
            }
            else{
                week_day_of_point_day+=1;
                point_year+=1;
            }
        }
    }

    while (week_day_of_point_day<0){    //將星期數整理在0~6
        week_day_of_point_day+=7;
    }
    while (week_day_of_point_day>6){    //將星期數整理在0~6
        week_day_of_point_day-=7;
    }

    return week_day_of_point_day;
}


int print_months(int point_day, int week_day, int is_leap_year, int specific_month){
    char months[13][10]={"", "January", "February", "March", "April", "May" , "June", "July", "August", "September"
                        , "October", "November", "December"};
    int days_in_a_month[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int a_year[72][7]={0};

    //閏年的2月有29天
    if (is_leap_year){
        days_in_a_month[2]=29;
    }

    //將week_day和point_day變成該月的1號
    week_day=week_day-((point_day-1)%7);
    point_day=1;
    if (week_day<0){
        week_day=week_day+7;
    }

    //將整年的日期全儲存到二維陣列內
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

    if (specific_month==0){     //印整年的年曆的程式
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
    else{       //印特定月份的程式
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


/* 學習日誌:
2022/11/09  1.開始製作萬年曆:輸入西元年,輸出整年的月曆;輸入西元年跟月,輸出那個月的月曆(以下為維基百科資料)
            2.基準日:2000/2/29為星期二,4/4,6/6,8/8,10/10,12/12,5/9,9/5,7/11,11/7的星期都與基準日相同
            3.每100年的基準日星期數按以下規律:星期二、星期日、星期五、星期三
            4.每過一個平年,基準日的星期數加1,每過一個閏年,基準日星期數加2;每過12年,基準日的星期數加1

2022/11/11  1.想透過將月曆拆分成星期的方式,製作一個副程式,用星期來組合成月;  這個想法後來改掉了 

2022/11/12  1.製作出能印出一個月月曆的副程式,參數是 月份、日期、星期;  後來也改掉,因為這樣沒辦法以 三個月為一列 印出來 

2022/11/13  1.判決日法則,計算出去年2月的最後一天(判決日)為星期幾,則今年的1/9的星期也會一樣
            2.基準:2000年的判決日為星期二,每過12年的判決日星期數加1 (2022/11/09的4.)
            3.製作計算去年判決日的程式,酸出今年1/9的星期,最後印出今年的年曆
*/
