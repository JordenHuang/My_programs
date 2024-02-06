import os

print('Welcome to 終極密碼!\nPlease enter the answer you want')

ans =""         #定義變數ans為空字串 / set variable ans to empty string

ansOK = False   #使用一個變數ansOK當while的條件(也能使用while True，再用continue和break)
                #the condition of while, you can also use while True, then use continue and break

#判斷要設定的答案是否為整數以及是否在範圍內 / check the type and the range of the answer
while not ansOK:
    ans = input('Enter the answer(0~100, 0 and 100 can\'t be the answer): ')
    try:
        ans = int(ans)
        if -1 < ans < 101:
            ansOK = True
        else:
            print('Enter number between 0 and 100!!')
    except ValueError:
        print('Enter number between 0 and 100!!')
TrueAns = int(ans)

#清除螢幕 / clear the screen
os.system('cls')

#設定答案範圍為 0~100 / set the answer range between 0 and 100
print('Welcome to 終極密碼!')
min = 0
max = 100

#使用try except來判斷使用者是否輸入整數 / use try except to check the input is integer number or not
while True:
    guess = input(f'Enter your guess({min}~{max}): ')
    try:
        guess = int(guess)
    except ValueError:
        print('','VALUE ERROR!! Please enter integer numbers')
        continue        #使用continue跳回while迴圈的開頭 / use continue to return to the beginning of the while loop

    #判斷數字範圍 / check the number range
    if min < guess < max:

        #沒猜中跳回一開始的while迴圈，繼續輸入數字 / if not guess right, return to the beginning of the while loop
        if guess < TrueAns:
            print('', 'Pass!')
            min = guess
        if guess > TrueAns:
            print('', 'Pass!')
            max = guess

        #猜中則跳出迴圈 / if guess right, leave the loop
        if guess == TrueAns:
            print('', 'Boom!!!\nYou lost')
            break


    # 輸入範圍不正確則提醒，並跳回一開始的while迴圈，繼續輸入數字
    # if not in the range, print 'out of range' and return to the beginning of the while loop
    else:
        print('', f'Out of range!! Please enter between {min} and {max}')
