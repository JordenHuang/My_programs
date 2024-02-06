import random
answer = random.randint(1,10)
secret = str(answer)
guess = ""
guess_count = 0
guess_limit = 3
out_of_guesses = False
#print(type(answer))
print("這是一個猜數字的遊戲，你有三次機會")
while guess != secret and not(out_of_guesses):
    if guess_count < guess_limit :
        guess = input("輸入一個0-10的數字: ")
        guess_count += 1
        if not guess.isdigit():
            print("就說了是數字")
            continue
        int_guess = int(guess)
        if  int_guess > 10:
            print("10以內阿傻逼")
        elif guess != secret:
            print("你錯了，低能兒")
    else:
        out_of_guesses = True

if out_of_guesses:
    print("真的是低能兒")
else:
    print("答對了，但你依然是低能兒")
if out_of_guesses:
    print("答案是" + secret)
