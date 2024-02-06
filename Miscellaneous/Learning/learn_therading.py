import threading
import time


def one():
    a = 0
    while a < 10:
        a += 1
        print(a)
#        time.sleep(1)

def two():
    b = 0
    while b < 20:
        b += 2
        print(b)
#        time.sleep(1)


t1 = threading.Thread(target=one)
t2 = threading.Thread(target=two)

t1.start()
t2.start()
