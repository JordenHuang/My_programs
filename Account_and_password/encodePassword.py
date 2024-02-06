fh = open('UserPassword.txt', 'a+', encoding='UTF-8')
fh.seek(0)
text = fh.readlines()
character = []
store = []
for line in text:
    lineSplit = line.replace('/', ' ').split()
    print(lineSplit[1])
    str_lineSplit = str(lineSplit[1])
    character = list(str_lineSplit)
    print(character)
    for i in character:
        store = list(store)
        store.append(chr(ord(i)+13531))



with open('realPassword.txt', mode='a', encoding='UTF-8') as f:
    store = '/'.join(store)
    print(store)
    f.write(store + '\n')


fh.close()