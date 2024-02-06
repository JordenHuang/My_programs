def MultTable(L, R):
    for left in L:
        for right in R:
            print('{} * {} = {}'.format(left, right, left*right))

if __name__ == '__main__':
    lRange = range(9, 12)
    rRange = range(8, 11)
    MultTable(lRange, rRange)
