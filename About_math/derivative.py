from cProfile import label
import numpy
from matplotlib import pylab


def function(x):
    return (2+numpy.sin(x/pi)) / (2-numpy.sin(x/pi))

def df(x, h):
    return (function(x+h)-function(x)) / h

pi = numpy.pi
min, max, points = 0, 50, 1000

xp = pylab.linspace(min, max, points)
yp = function(xp)   #f(x)

h = (max-min)/(points-1)
dyp = df(xp, h)        #df(x)


pylab.figure(figsize=(8,4))
pylab.plot(xp, yp,lw=2, label="f(x)") 
pylab.plot(xp, dyp, label="computed f'(x)")

pylab.title("f(x) = (2+sin(x/pi))/(2-sin(x/pi)) and computed derivative")
pylab.legend(loc=2)
pylab.xlabel("X")
pylab.ylabel("Y")
pylab.grid()
pylab.show()