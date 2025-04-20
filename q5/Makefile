TARGET = profiling
SRC = profiling.cpp
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -pg

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET) gmon.out

