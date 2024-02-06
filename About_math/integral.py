import pylab

pi = pylab.pi

a, b, n = 1, 2, 100

xs, h = pylab.linspace(a, b, n+1, retstep=True)
#print(xs)

ys = xs * pylab.sqrt(2*xs - 1)

# rec_sum 矩形面積
# d_sum 下矩形面積, u_sum 上矩形面積, t_sum 梯形面積
rec_sum, d_sum, u_sum, t_sum = 0, 0, 0, 0

y1 = ys[0]

for y2 in ys[1:]:
    rec_sum += y1
    if y1 < y2:
        d_sum += y1
        u_sum += y2
    else:
        d_sum += y2
        u_sum += y1
        
    t_sum += y1 + y2
    y1=y2
    
rec_sum *= h
d_sum *= h
u_sum *= h
t_sum *= h/2

#正確解
correct_sum = 2.158204464

print("迴圈求積: ")
print("矩形積分   :", round(rec_sum, 9), "誤差:", round(abs(correct_sum - rec_sum), 10))
print("上矩形積分 :", round(u_sum, 9), "誤差:", round(abs(correct_sum - u_sum), 10))
print("下矩形積分 :", round(d_sum, 9), "誤差:", round(abs(correct_sum - d_sum), 10))
print("梯形積分法 :", round(t_sum, 9), "誤差:", round(abs(correct_sum - t_sum), 10))
