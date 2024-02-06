import numpy

#   x + 4y + 2z =  1
#  3x      -  z = -2
# -2x + 4y + 3z =  3

matrix_A = numpy.array([[1, 4, 2],
                        [3, 0, -1],
                        [-2, 4, 3]])

matrix_B = numpy.array([1, -2, 3]).reshape(3, 1)

inverse_A = numpy.linalg.inv(matrix_A)

ans = inverse_A * matrix_B

print(ans) # Singular matrix (noninvertible)