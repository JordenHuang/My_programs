'''def LookupDicts(word):
    outList = []
    if word in english:
        outList.append(f'in English: {english[word]}')
    if word in spanish:
        outList.append(f'in Spanish: {spanish[word]}')
    if word in french:
        outList.append(f'in French: {french[word]}')
    return outList


english = {'one':1, 'pan':'鍋子', 'caggabe':'高麗菜', 'pie':'派餅'}
spanish = {'uno':1, 'pan':'麵包', 'col':'高麗菜', 'pie':'腳'}
french = { 'une':1, 'tol':'你', 'col':'衣領', 'pie':'鵲'}

word = input('enter word to look up: ')
outList = LookupDicts(word)
if not outList:
    print(f'{word} not found in all dictionary')
else:
    print('\n'.join(outList))
'''
#-----------------------------------------------------------------------------------------------------------------------
'''
def leap(year):
    if year % 400 == 0:
        return True
    elif year % 4 == 0:
        if year % 100 == 0:
            return False
        else:
            return True
    else:
        return False

print(leap(int(input("Enter a year: "))))


def easy_leap(year):
    return year % 400 == 0 or year % 4 == 0 and year % 100 != 0

print(easy_leap((int(input('Enter a year: ')))))
'''
#-----------------------------------------------------------------------------------------------------------------------
'''
def StackInterpreter():
    L = []
    while True:
        line = input('command: ')
        word = line.split()
        if len(word) == 0:
            pass
        elif word[0] == 'show':
            print(L)
        elif word[0] == 'push':
            L.extend(word[1:])
        elif word[0] == 'pop':
            print(L.pop())
        elif word[0] == 'quit':
            break
        else:
            print('Unknow commond')

StackInterpreter()
'''
#-----------------------------------------------------------------------------------------------------------------------
'''
D = { 'rate': 0.0}
def totalWithTax(*names, **kv):
    global D
    total = 0.0
    for name in names:
        if type(name) in {int, float}:
            total += name
        else:
            total += D[name]
    for kw, val in kv.items():
        D[kw] = val
        if kw != 'rate':
            total += val
    return total * (1 + D['rate'])

if __name__ =='__main__':
    assert totalWithTax(rate=0.05, apple=20, oranges=15, guava=12) == 49.35
    assert totalWithTax('apple', 'guava') == 33.6
    assert totalWithTax(23, 45, 'oranges', mango=60) == 150.15
'''
#-----------------------------------------------------------------------------------------------------------------------
'''
def rec_find(L, val):
    if type(L) in {list, tuple}:    #if look inside members of L
        for i, v in enumerate(L):
            p = rec_find(v, val)    #recursively find each member
            if p == True:           #L[i] == val, so we return (i,)
                return (i,)
            if p != False:          #L[i] recursively found val,
                return (i,) + p     #so we prepend i to its path p
    return L == val                 #either L is not seq or for-loop didn't find
'''
#-----------------------------------------------------------------------------------------------------------------------
'''
def indent_list(L, level=0):
    if L == None:
        return
    if type(L) in {list, tuple}:
        for child in L:
            indent_list(child, level+1)
    else:
        print(f'{" "*4*level}{L}')

if __name__ == '__main__':
    L = ['F1', ['F4', 'F5', ['F8']], 'F2', 'F3', 'D3', ['F6', 'F7']]
    indent_list(L)

'''
#-----------------------------------------------------------------------------------------------------------------------
'''
def number_outline(L, prefix=()):
    if type(L) in {list, tuple}:
        #keep prefix[-1], extend by new dimension, starting from 1
        i = 0
        for v in L:
            if type(v) not in {list, tuple}:
                i += 1
            number_outline(v, prefix+(i,))
            #don't increment if v is a list/tuple
    #outerwise, indent and join the prefix together by '.'
    else:
        s = ' ' * 4*(len(prefix)-1)
        s += '.'.join(map(str, prefix))
        s += '. ' + L
        print(s)


if __name__ == '__main__':
    L = ['F1', ['F4', 'F5', ['F8']], 'F2', 'F3', 'D3', ['F6', 'F7']]
    number_outline(L)

'''
#-----------------------------------------------------------------------------------------------------------------------

class Mylist(list):     #inherits from built-in list class
    def __repr__(self):
        return self.__class__.__name__+'('+super().__repr__()+')'

    def find(self, val):
        def rec_find(L, val):
            if isinstance(L,list) or isinstance(L, tuple):
                for i, v in enumerate(L):
                    p = rec_find(v, val)
                    if p == True:
                        return (i,)
                    if p != False:
                        return (i,)+p
            return L == val
        return rec_find(self, val)

    def sort(self, key=None, reverse=False):
        D = {'NoneType': 0, 'int': 1, 'float': 1, 'str': 2, 'tuple': 3, 'list': 4}
        return super().sort(key=lambda x:(D.get(type(x).__name__, 5), key(x) if key is not None else x), reverse= reverse)

if __name__ == '__main__':
    L = Mylist([1, 2, 3])
    M = Mylist([3, 8, 'hello', 7.4, ('world', 15), [4, 7]])
    N = Mylist([7.4, 2, 'world', 'bye', (13, 24), 'bye', (14, 28), None])
    P = Mylist([7.4, Mylist([2,	(5,	'a','z'),[4,[9,	7],	'b']]),2 ,'world','bye',(13,24),'bye',(14,28),None])
    P.find(100), P.find('z'), P.find([9, 7]), P.find((13, 24))
