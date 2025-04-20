#include "mandelbrot.h"
using namespace std;

bool is_in_mandelbrot(complex<double> c, int N) {
    int M = 2;
    complex<double> a = 0;

    for (int i = 0; i < N; i++)
    {
        a = a*a + c;
    }
    return abs(a) <= M;
}

