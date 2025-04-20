CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11
LDFLAGS = -shared
TARGET_LIB = libmandelbrot.so

all: $(TARGET_LIB) main

$(TARGET_LIB): mandelbrot.o
	$(CXX) $(LDFLAGS) -o $@ $^

mandelbrot.o: mandelbrot.cpp mandelbrot.h
	$(CXX) $(CXXFLAGS) -fPIC -c mandelbrot.cpp

main.o: main.cpp mandelbrot.h
	$(CXX) $(CXXFLAGS) -c main.cpp

main: main.o $(TARGET_LIB)
	$(CXX) -o $@ main.o -L. -lmandelbrot
	
run:
	 LD_LIBRARY_PATH=. ./main

clean:
	rm -f *.o *.so main
