from random import choice


main_dish = {'蝦仁炒飯':60, '牛肉麵':100, '豬肉丼飯':120, '滷肉飯': 40}
sub_main_dish = {'蛋花湯':40, '餛飩湯':50, '清湯':1000}

a = choice(list(main_dish.items()))
b = choice(list(sub_main_dish.items()))

print('What I eat today:')
print(f'{a[0]}: {a[1]}')
print(f'{b[0]}: {b[1]}')
print(f'I spend: {int(a[1]) + int(b[1])}')