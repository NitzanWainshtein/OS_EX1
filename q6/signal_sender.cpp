#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

int main() {
    pid_t recv_id;
    unsigned int temp;
    unsigned char message;

    cout << "Enter receiver PID: ";
    cin >> recv_id;

    cout << "Enter message: ";
    cin >> temp;

    if (temp > 255) {
        cout << "Error: Message must be between 0 and 255.\n" << endl;
        return 1;
    }

    message = (unsigned char) temp;

    for (int i = 7; i >= 0; i--) {
        int bit = (message >> i) & 1;
        int signal_to_send = bit ? SIGUSR2 : SIGUSR1;

        if (kill(recv_id, signal_to_send) == -1) {
            perror("kill failed");
            return 1;
        }

        usleep(1000);
    }

    return 0;
}
