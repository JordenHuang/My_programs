with open('story1.txt', 'w', encoding='utf-8') as astory:
    astory.write('1.有一天小明去圖書館\n')
    astory.write('小明：我要一碗牛肉麵\n')
    astory.write('櫃檯：先生 這裡是圖書館 . . .\n')
    astory.write('小明：喔喔好 （氣音）我要一碗牛肉麵\n')
with open('story2.txt', 'w', encoding='utf-8') as bstory:
       bstory.write('2. 有一天小明他爸很渴 就叫小明幫他倒水\n')
       bstory.write('但小明遲遲沒去倒\n')
       bstory.write('小明爸就說：「你是要逼爸渴死嗎？」\n')
       bstory.write('於是小明就開始B Box了\n')
astory = open('story1.txt', 'r', encoding='utf-8')
bstory = open('story2.txt', 'r', encoding='utf-8')
print(astory.read())
print(bstory.read())
astory.seek(0)
print(astory.readline())
astory.close()
bstory.seek(0)
print(bstory.readline())
bstory.close()