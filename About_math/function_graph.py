import numpy
from matplotlib import pylab


def function(x):
    return numpy.sin(x) / abs(2*x)

pi = numpy.pi
min, max, points = -10*pi, 10*pi, 1000

xp = pylab.linspace(min, max, points)
yp = function(xp)

pylab.title("sin(x)/|2x|")
pylab.xlabel("X")
pylab.ylabel("Y")
pylab.plot(xp, yp)
pylab.grid()
pylab.show()