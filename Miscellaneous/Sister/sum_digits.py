'''
題目一： 輸入一正整數，輸出每一位數加總的和

範例測資一：
input: 123456789
output: 45


範例測資二：
input: 1000
output: 1

範例測資三：
input: 0
output: 0
'''

def summing_digits(num:str):
    ans = 0
    for i in range(len(num)):
        ans += int(num[i])
    return ans

def summing_digits_method_2(num:int):
    ans = 0
    while num > 0:
        ans += num % 10
        num = num // 10
    return ans

num = input("Enter a number: ")
print(summing_digits(num), "(using method 1)")
print(summing_digits_method_2(int(num)), "(using method 2)")



'''
題目二： 連續輸入正整數，輸入一個數後馬上輸出結果，直到輸入-1停止。
        輸出每個正整數的每一位數加總的和

範例測資一：
input: 123456789
output: 45
input: 100000001
output: 2
input: 0
output: 0
input: 987654321
output: 45
'''

while True:
    num = input("Enter a number (-1 to quit): ")
    if num == "-1":
        break
    print(summing_digits(num))