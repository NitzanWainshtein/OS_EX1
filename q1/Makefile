all: divByZero stackOverflow undefinedMemory

divByZero: divByZero.cpp
	g++ -g $< -o $@

stackOverflow: stackOverflow.cpp
	g++ -g $< -o $@

undefinedMemory: undefinedMemory.cpp
	g++ -g $< -o $@

clean:
	rm -f divByZero stackOverflow undefinedMemory core.*
