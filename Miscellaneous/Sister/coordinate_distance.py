'''
題目一： 輸入兩平面座標，例：(a,b) 和 (c,d)。輸入及輸出格式如同範例測資
        輸出兩座標之間的距離，即 |(a,b) - (c,d)|

範例測資一：
input: 
輸入座標1: 3 4
輸入座標2: 0 0

output: 
兩座標間的距離為: |(3,4) - (0, 0)| = 5


範例測資二：
input: 
輸入座標1: 5 7
輸入座標2: -5 -7

output: 
兩座標間的距離為: |(5, 7) - (-5,- 7)| = 17.204650534085253


範例測資三：
輸入座標1: 0 0
輸入座標2: -60 -80

output: 
兩座標間的距離為: |(0, 0) - (-60, -80)| = 100
'''

import math

def coordinate_distance(c1:tuple, c2:tuple):
    dis = 0
    
    if len(c1) != len(c2):
        print("兩座標的座標軸數不相同，兩座標不在同維度")
        return None
    
    for i in range(len(c1)):
        dis += math.pow(abs(c1[i] - c2[i]), 2)
    
    dis = math.sqrt(dis)
    return dis

c1 = tuple(map(int, input("輸入座標1: ").split()))
c2 = tuple(map(int, input("輸入座標2: ").split()))

print(f"兩座標間的距離為: |{c1} - {c2}| = {coordinate_distance(c1, c2)}\n")



'''
題目二： 連續輸入平面座標，直到遇到End Of File (Ctrl + z)。輸入及輸出格式如同範例測資
        輸出在這些座標中，哪兩個座標點間有最大的距離。

範例測資一：
input: 
0 0
-1 1
5 12
8 15
^Z

output: 
相聚最遠的座標為: (0, 0), (8, 15)
距離為: 17


範例測資二：
input: 
3 4
-5 -7
6 8
-5 7
15 -1
^Z

output: 
相聚最遠的座標為: (-5, 7), (15, -1)
距離為: 21.540659228538015
'''

largest = [tuple(), tuple(), 0]
coordinate_list = []
while True:
    try:
        c = tuple(map(int, input().split()))
        coordinate_list.append(c)
    except EOFError:
        break

for i in range( len(coordinate_list) - 1 ):
    for j in range(1, len(coordinate_list)):
        c1 = coordinate_list[i]
        c2 = coordinate_list[j]
        distance = coordinate_distance(c1, c2)
        
        if distance > largest[2]:
            largest[0] = c1
            largest[1] = c2
            largest[2] = distance

print(f"相聚最遠的座標為: {largest[0]}, {largest[1]}")
print(f"距離為: {largest[2]}")