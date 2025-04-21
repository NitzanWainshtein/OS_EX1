#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

volatile sig_atomic_t received_value = 0;
volatile int bit_index = 7;

void handle_SIGUSR1(int sig) {
    bit_index--;
}

void handle_SIGUSR2(int sig) {
    received_value |= (1 << bit_index);
    bit_index--;
}

int main() {
    cout << "My PID is " << getpid() << endl;

    struct sigaction sa1, sa2;

    sa1.sa_handler = handle_SIGUSR1;
    sigemptyset(&sa1.sa_mask);
    sigaddset(&sa1.sa_mask, SIGUSR2);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    sa2.sa_handler = handle_SIGUSR2;
    sigemptyset(&sa2.sa_mask);
    sigaddset(&sa2.sa_mask, SIGUSR1);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);

    while (bit_index >= 0) {
        pause();
    }

    cout << "Received " << (int)received_value << endl;
    return 0;
}