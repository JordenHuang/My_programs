L = [ 12, -59, 789, -5, 0 ]
print(L)
positive, negative, zero = (0, 0, 0 )
for i in L :
    if i<0:
        positive +=1
    elif i>-0 :
        negative += 1
    else:
        zero += 1
print('positive: %d, negative: %d, zero: %d' % (positive, negative, zero))


