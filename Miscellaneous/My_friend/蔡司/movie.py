Movies = {'1': '1.野蠻遊戲', '2': '2.天才少女福爾摩斯', '3': '3.香草天空', '4': '4.你的名字', '5': '5.格雷的69道陰影'}
Times = {'1': '1.星期一下午5點', '2': '2.星期二下午5點', '3': '3.星期三下午5點', '4': '4.星期四下午5點', '5': '5.星期五下午5點', \
         '6': '6.星期一晚上9點', '7': '7.星期二晚上9點', '8': '8.星期三晚上9點', '9': '9.星期四晚上9點', '10': '10.星期五晚上9點'}
while True:
    print('目前上映的院線片:')
    print(Movies['1'], Movies['2'], Movies['3'], Movies['4'], Movies['5'])
    select = input('輸入你想看的電影序數...')
    int_select = int(select)

    if int_select != 1 :
        print("請重新輸入")
        break

    if int_select == -1:
        print("掰掰")
        break

    if (int_select == 1):
        print('野蠻遊戲')
        print(Times['1'], Times['8'])
        select2 = input('請問想挑選哪個時間觀賞...')
        int_select2 = int(select2)
        if (int_select2 == 1):
            print('星期一下午5點')
        else:
            print('星期三晚上9點')
        card = input('是否為高大學生(只能輸入是或否):')
        if (card == '是'):
            print('票價為100元')
            print('訂票成功，感謝你的配合\n')
        elif (card == str('否')):
            print('票價為300元')
            print('訂票成功，感謝你的配合\n')
        else:
            print('亂打請從新開始\n')
            continue

    elif (int_select == 2):
        print('天才少女福爾摩斯')
        print(Times['2'], Times['7'])
        select3 = input('請問想挑選哪個時間觀賞...')
        int_select3 = int(select3)
        if (int_select3 == 1):
            print('星期二下午5點')
        else:
            print('星期二晚上9點')
        card = input('是否為高大學生(只能輸入是或否):')
        if (card == str('是')):
            print('票價為100元')
            print('訂票成功，感謝你的配合\n')
        elif (card == str('否')):
            print('票價為300元')
            print('訂票成功，感謝你的配合\n')
        else:
            print('亂打請從新開始\n')
            continue

    elif (int_select == 3):
        print('香草天空')
        print(Times['3'], Times['6'])
        select4 = input('請問想挑選哪個時間觀賞...')
        int_select4 = int(select4)
        if (int_select4 == 1):
            print('星期三下午5點')
        else:
            print('星期一晚上9點')
        card = input('是否為高大學生(只能輸入是或否):')
        if (card == str('是')):
            print('票價為100元')
            print('訂票成功，感謝你的配合\n')
        elif (card == str('否')):
            print('票價為300元')
            print('訂票成功，感謝你的配合\n')
        else:
            print('亂打請從新開始\n')
            continue

    elif (int_select == 4):
        print('你的名字')
        print(Times['5'], Times['9'])
        select6 = input('請問想挑選哪個時間觀賞...')
        int_select6 = int(select6)
        if (int_select6 == 1):
            print('星期五下午5點')
        else:
            print('星期四晚上9點')
        card = input('是否為高大學生(只能輸入是或否):')
        if (card == str('是')):
            print('票價為100元')
            print('訂票成功，感謝你的配合\n')
        elif (card == str('否')):
            print('票價為300元')
            print('訂票成功，感謝你的配合\n')
        else:
            print('亂打請從新開始\n')
            continue

    elif (int_select == 5):
        print('格雷的69道陰影')
        age = input('請輸入你的年紀:')
        int_age = int(age)
        if (int_age <= 18):
            print('你的年紀太小不足以觀賞這部電影\n')
        elif (int_age >= 18):
            print('可以觀賞')
            print(Times['4'], Times['10'])
            select5 = input('請問想挑選哪個時間觀賞...')
            int_select5 = int(select5)
            if (int_select5 == 1):
                print('星期四下午5點')
            else:
                print('星期五晚上9點')
            card = input('是否為高大學生(只能輸入是或否):')
            if (card == str('是')):
                print('票價為100元')
                print('訂票成功，感謝你的配合\n')
            elif (card == str('否')):
                print('票價為300元')
                print('訂票成功，感謝你的配合\n')
            else:
                print('亂打請從新開始\n')
                continue
