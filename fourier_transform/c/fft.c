#include <stdio.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159
#define N ((int)pow(2, 15))

void dft(float *in, float complex *out)
{
    int f, i;
    float t;
    for (f = 0; f < N; ++f) {
        out[f] = 0.f + 0.f * I;
        for (i = 0; i < N; ++i) {
            t = (float)i / N;
            out[f] += in[i] * cexp(2 * I * PI * f * t);
        }
    }
}

void fft_recursive(float *in, float complex *out, int len)
{
    if (len <= 1) {
        out[0] = in[0];
        return;
    }

    len = len >> 1;
    int i, f;
    float t;
    float complex omega;

    float even[len];
    float odd[len];
    float complex out_even[len];
    float complex out_odd[len];
    // Prepare even and odd part of in
    for (i = 0; i < len; ++i) {
        even[i] = in[(i << 1)];
        odd[i] = in[(i << 1) + 1];
    }

    fft_recursive(even, out_even, len);
    fft_recursive(odd, out_odd, len);

    // Combine them
    for (f = 0; f < len; ++f) {
        t = (float)f / (len << 1);
        omega = cexp(I * 2 * PI * t) * out_odd[f];
        out[f] = out_even[f] + omega;
        out[f + len] = out_even[f] - omega;
    }
}

int bit_reverse(int num)
{
    int i, r = 0;
    for (i = 0; i < log2(N); ++i) {
        r <<= 1;
        r |= (num & 1);
        num >>= 1;
    }
    return r;
}

void fft_iterative(float *in, float complex *out, int *swap_idx)
{
    int i, j, k;
    int m, m2;
    float complex t, u;
    float complex omega, omega_m;
    // Bit reverse
    for (i = 0; i < N; ++i) {
        // out[i] = in[bit_reverse(i)];
        out[i] = in[swap_idx[i]];
        // printf("out[%d] = %.2f, %.2f\n", i, creal(out[i]), cimag(out[i]));
    }

    for (i = 1; i <= log2(N); ++i) {
        m = 1 << i;
        m2 = m >> 1;
        omega_m = cexp(I * 2 * PI / m);
        for (k = 0; k < N; k += m) {
            omega = 1.f;
            for (j = 0; j < m2; ++j) {
                t = omega * out[k + j + m2];
                u = out[k + j];
                out[k + j] = u + t;
                out[k + j + m2] = u - t;
                omega *= omega_m;
            }
        }
    }
}

void calc_swap_idx(int *swap_idx)
{
    int i;
    for (i = 0; i < N; ++i) {
        swap_idx[i] = bit_reverse(i);
    }
}

void plot_wave(float *in, int scale)
{
    int x, y, k;
    for (x = 0; x < N; ++x) {
        y = (in[x] + scale/4) * scale;
        for (k = 0; k < y; ++k) {
            printf(" ");
        }
        printf("*");
        printf("\n");
    }
}

int main(void)
{
    float in[N];
    float complex out[N];
    int i, freq = 2;
    float t;
    int swap_idx[N];
    calc_swap_idx(swap_idx);

    for (i = 0; i < N; ++i) {
        in[i] = 0.f;
    }

    for (i = 0; i < N; ++i) {
        t = (float)i / N;
        freq = 2;
        in[i] += cosf(2 * PI * freq * t);
        freq = 3;
        in[i] += sinf(2 * PI * freq * t);
        // printf("in[%d] = %f\n", i, in[i]);
    }

    // dft(in, out);
    // fft_recursive(in, out, N);
    fft_iterative(in, out, swap_idx);

    // plot_wave(in, 8);

    for (i = 0; i < N; ++i) {
        printf("%d: %0.2f, %0.2f\n", i, creal(out[i]), cimag(out[i]));
    }
    return 0;
}
