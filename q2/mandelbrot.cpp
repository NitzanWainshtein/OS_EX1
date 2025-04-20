#include <iostream>
#include <string>
#include <complex>
using namespace std;


bool isMandelbrot(complex<double> mandel, int M = 2){

    return abs(mandel) <= M;
}

complex<double> recursive(complex<double> c ,int N = 1000){
    complex<double> a = 0;
    for(int i = 0; i < N ; i++){
        a = a*a + c;
    }
    return a;
}


int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        cerr << "Usage example: " << argv[0] << " <real> <imag> [N]" << endl;
        return 1;
    }

    double re, im;
    int N = 1000;

    try {
        re = stod(argv[1]);
        im = stod(argv[2]);
        if (argc == 4) {
            N = stoi(argv[3]);
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: one of the arguments is not a valid number." << endl;
        return 1;
    } catch (const out_of_range& e) {
        cerr << "Error: one of the arguments is out of range." << endl;
        return 1;
    }

    complex<double> c(re, im);
    complex<double> mandel = recursive(c, N);

    if (isMandelbrot(mandel)) {
        cout << re << " + " << im << "i is in the Mandelbrot set" << endl;
    } else {
        cout << re << " + " << im << "i is not in the Mandelbrot set" << endl;
    }

    return 0;
}

