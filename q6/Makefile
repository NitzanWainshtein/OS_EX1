all: signal_sender signal_receiver

signal_sender: signal_sender.cpp
	g++ -Wall -o signal_sender signal_sender.cpp

signal_receiver: signal_receiver.cpp
	g++ -Wall -o signal_receiver signal_receiver.cpp

clean:
	rm -f signal_sender signal_receiver
