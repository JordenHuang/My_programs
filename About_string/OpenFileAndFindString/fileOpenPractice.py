ToFind = input('Enter a word you want to find in hello.txt: ')

print(f'\nThe word you want to find is "{ToFind}"')

with open('hello.txt', 'r',encoding='UTF-8') as fh:
    text = fh.readlines()
    lineNumber = 0
    total = []
    for line in text:
        lineNumber += 1
        if line.find(ToFind) != -1:
            position = [i+1 for i in range(len(line)) if line.startswith(ToFind, i)]
            total.extend(position)
            print('\nLine number:',lineNumber)
            print('Position:',position)

    if ToFind not in str(text):
        print('Not in the file')

    print('\nTotal find =',len(total))

