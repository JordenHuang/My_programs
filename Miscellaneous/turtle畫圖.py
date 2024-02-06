import turtle as tur
import colorsys as cs


tur.bgcolor('black')
tur.speed(0)
tur.width(1)

def square(x):
    for i in range(4):
        tur.forward(x)
        tur.left(90)

def shape(x):
    tur.forward(x)
    tur.left(45)
    tur.forward(x)
    tur.right(60)
    tur.width(3)
    square(x)
    tur.width(1)
    tur.right(165)
    tur.forward(x)
    tur.left(45)
    tur.forward(x)
h = 0.0
for i in range(90):
    tur.color(cs.hsv_to_rgb(h, 1, 1))
    tur.circle(30, 4)
    tur.right(90)
    shape(70)
    tur.right(135)
    h += 0.0111

tur.done()
