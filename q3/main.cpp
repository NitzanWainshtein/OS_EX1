#include <iostream>
#include <complex>
#include "mandelbrot.h"

using namespace std;
int main() {

    double re, im;
	cout << "Enter values for <re> <im>: " << endl;
    while(scanf("%lf %lf" , &re ,&im) == 2)
    {
        if(re == 0.0 && im == 0.0){
        	cout << "program terminated" << endl;
            return 0;
        }

        complex<double> c(re,im);
        int N = 1000;

        if(is_in_mandelbrot(c, N)){
            cout << re <<" + " << im << "i is in the Mandelbrot set" << endl;
        } else {
            cout << re << " + " << im << "i is not the Mandelbrot set" << endl;
        }
	
	cout << "\nEnter another complex number (re im), or 0 0 to quit:" << endl;
    }

    return 0;
}
