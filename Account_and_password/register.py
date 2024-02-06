import datetime


def username_ck(username):
    if username != '':
        assert username.isalnum(), 'No special characters in username!!'
        assert len(username) <= 12, 'The length of username must less than 12 character!!'
        assert username.isascii(), 'Only English or numbers in username!!'
    else:
        raise ValueError('Nothing entered!!')
    return username
def password_ck(password):
    if password != '':
        assert password.isalnum(), 'No special characters in password!!'
        assert len(password) <= 20, 'The length of password must less than 20 character!!'
        assert password.isascii(), 'Only English or numbers in password!!'
    else:
        raise ValueError('Nothing entered!!')
    return password


fh = open('UserPassword.txt',mode='a+',encoding='UTF-8')
fh.seek(0)
text = fh.readlines()
AP = []

username = input('Enter your Username: ')
username_ck(username)
AP.append(username)

for line in text:
    lineSplit = line.replace('/', ' ').split()
#    print(lineSplit[0])
    assert AP[0] != lineSplit[0], 'This username has been used!'

password = input('Enter your password: ')
password_ck(password)

realPassword = open('realPassword.txt', 'a', encoding='UTF-8')
realPassword.write(password + '\n')

encodePassword = []
for element in password:
    encodePassword.append(chr(ord(element)+13531))
#print(encodePassword)
encodePassword = ','.join(encodePassword)
AP.append(encodePassword)

ap = '/'.join(AP)
fh.write(ap + '/' + str(datetime.date.today()) + '\n')
print('Register successfully !')

fh.close()