CXX = g++
CXXFLAGS = -Wall -Wextra -g -fprofile-arcs -ftest-coverage
TARGET = dijkstra
SRC = dijkstra.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.gcno *.gcda *.gcov
