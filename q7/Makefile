CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGETS = add2PB findPhone

all: $(TARGETS)

# Build add2PB
add2PB: add2PB.cpp
	$(CXX) $(CXXFLAGS) -o add2PB add2PB.cpp

# Build findPhone
findPhone: findPhone.cpp
	$(CXX) $(CXXFLAGS) -o findPhone findPhone.cpp

clean:
	rm -f $(TARGETS) *.o

