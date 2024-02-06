lusername = input('Enter your username: ')
decodePassword = []
store = []
end = []

with open('UserPassword.txt', encoding='UTF-8') as fh:
    text = fh.readlines()
    for line in text:
        lineSplit = line.replace('/', ' ').split()
        wrongUsername = True
#        print(lineSplit[0])

        if lusername == lineSplit[0]:
            wrongUsername = False
            store.append(str(lineSplit[1]))

            for element in store:
                decodePassword = list(element.replace(',', ''))
#                print(decodePassword)


                for i in decodePassword:
                    end.append(chr(ord(i) - 13531))

#            print(end)
            end = ''.join(end)
#            print(decodePassword)
#            print(end)
            lpassword = input('Enter your password: ')
#            print(lineSplit[1])

            if lpassword == end:
                print('Login successfully, Welcome')
                break
            else:
                print('Wrong password !!')
                break

    if wrongUsername:
        print('Wrong username !!')


'''
def hidden_password(message:str):
    print(message, end='')
    password = ''
    while True:
        symbol = getch().decode('utf-8')
        if symbol == '\n' or symbol == '\r':
            break
        elif symbol == '\b':
            print("\b ", end='\b')
            password = password[0:len(password)-1]
        else:
            print("*", end='')
            password += symbol
    print()
    return password
'''