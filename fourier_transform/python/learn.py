from matplotlib import pyplot as plt
import math
import numpy as np

def play_square_wave(freq, number_of_terms):
    plt.ion()
    plt.title("Square wave")
    xs = [0] * 500
    ys = [0] * 500
    for i in range(1, number_of_terms, 2):
        x, y = generate_sin_wave(i*freq, 500, 1)
        for iy in range(len(y)):
            y[iy] = y[iy] * (1/i) * (4/math.pi)
        xs = [sum(x) for x in zip(xs, x)]
        ys = [sum(y) for y in zip(ys, y)]

        plt.cla()
        plt.plot(xs, ys)
        plt.pause(0.15)

# x = []
# y = []
# for i in range(200):
#     x.append(i/200)
#     y.append(math.sin(2 * math.pi * 2 * i/200))

# e^(i*x) = cos(x) + i*sin(x)

def generate_sin_wave(freq, sample_rate, seconds):
    x = []
    y = []
    for i in range(sample_rate * seconds):
        x.append(i/sample_rate)
        y.append(math.sin(2 * math.pi * freq * i/sample_rate))
    return x, y

def generate_cos_wave(freq, sample_rate, seconds):
    x = []
    y = []
    for i in range(sample_rate * seconds):
        x.append(i/sample_rate)
        y.append(math.cos(2 * math.pi * freq * i/sample_rate))
    return x, y


def dft(wave, sample_rate, seconds):
    out = [0+0j] * sample_rate
    for f in range(sample_rate):
        for i in range(len(wave)):
            # out[f] += wave[i] * math.sin(2*math.pi*f*(i/sample_rate))
            out[f] += wave[i] * (math.e**(2 * 1j * math.pi * f * (i / sample_rate)))
    return out

def fft(y):
    N = len(y)
    if N <= 1: return y

    even = fft(y[0::2])
    odd = fft(y[1::2])

    out = [0] * len(y)
    for f in range(N//2):
        t = math.e**(1j*2*math.pi*f/N) * odd[f]
        out[f] = even[f] + t
        out[f+(N//2)] = even[f] - t
    return out

def bit_reverse(num, N):
    result = 0
    # while num > 0:
    for _ in range(int(math.log2(N))):
        result <<= 1
        result |= (num & 1)
        num >>= 1
    return result

def iterative_fft(y):
    N = len(y)
    A = [0] * N
    # bit reverse
    for i in range(N):
        A[i] = y[bit_reverse(i, N)]

    for s in range(1, int(math.log2(N))+1):
        m = 2 ** s
        omega_m = math.e ** (1j * 2 * math.pi / m)
        for k in range(0, N, m):
            omega = 1
            for j in range(0, m//2):
                t = omega * A[k + j + m//2]
                u = A[k + j]
                A[k + j] = u + t
                A[k + j + m//2] = u - t
                omega *= omega_m
    return A


if __name__ == "__main__":
    # play_square_wave(5, 100)

    N = 2**8

    xs, ys = generate_sin_wave(2, N, 1)

    x, y = generate_cos_wave(5, N, 1)
    xs = [sum(x) for x in zip(xs, x)]
    ys = [sum(y) for y in zip(ys, y)]

    plt.title("Target wave")
    plt.plot(xs, ys)
    plt.show()

    # out = dft(ys, 200, 1)
    # out = fft(ys)
    out = iterative_fft(ys)

    plt.title("freqs")
    plt.plot([i for i in range(len(out))], [num.real for num in out])
    plt.plot([i for i in range(len(out))], [num.imag for num in out])
    plt.show()

    # for i in range(len(out)):
    #     if out[i].real > 0:
    #         print(f"{i}: {out[i].real}")
    #     if out[i].imag > 0:
    #         print(f"{i}: {out[i].imag}")

