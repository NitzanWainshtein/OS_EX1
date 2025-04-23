#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cctype>


using namespace std;

// Function to check if the name is valid
bool isValidName(const char* part) {
    for (int i = 0; part[i] != '\0'; ++i) {
        if (!isalpha(part[i]) && part[i] != ' ') {
            return false;
        }
    }
    return true;
}

// Function to check if the phone number is valid
bool isValidPhone(const char* phone) {
    for (int i = 0; phone[i] != '\0'; ++i) {
        if (!isdigit(phone[i]) && phone[i] != '-') {
            return false;
        }
    }
    return true;
}


int main(int argc, char *argv[]) {
    
    // Check if the number of arguments is correct 
    if (argc < 3) {
        cerr << "Usage: ./add2PB <full name> <phone number>\n";
        cerr << "Note: You may enter names with spaces without quotes.\n";
        return 1;
    }

    const char *phone = argv[argc -1];

    // Check if the phone number is valid
    if (!isValidPhone(phone)) {
        cerr << "Error: Phone number must contain digits and hyphens only.\n";
        return 1;
    }

    // Build the full name from argv[1] to argv[argc - 2]
    char name[256];
    int nameIndex = 0;

    for (int i = 1; i < argc - 1; ++i) {
        const char* part = argv[i];

        if (!isValidName(part)) {
            cerr << "Error: Name must contain letters and spaces only.\n";
            return 1;
        }

        int j = 0;
        while (part[j] != '\0') {
            name[nameIndex++] = part[j++];
        }

        // Add space between name parts (except after the last)
        if (i < argc - 2) {
            name[nameIndex++] = ' ';
        }
    }

    name[nameIndex] = '\0';
    

    int fd = open("phonebook.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    
    // Check if the file was opened successfully
     // O_WRONLY: Open for writing only
     // O_APPEND: Append to the end of the file
     // O_CREAT: Create the file if it does not exist
     // 0644: File permissions (read/write for owner, read for group and others)

    if (fd < 0) {
        cerr << "Error: failed to open phonebook.txt\n";
        return 1;
    }

    char buffer[512];
    int index = 0;

    // Write the name
    for (int i = 0; name[i] != '\0'; ++i) {
        buffer[index++] = name[i];
    }

    buffer[index++] = ',';
    
    // Write the phone number
    for (int i = 0; phone[i] != '\0'; ++i) {
        buffer[index++] = phone[i];
    }
    
    buffer[index++] = '\n'; // Newline
    buffer[index] = '\0';

    // Write to the file
    write(fd, buffer, index);
    close(fd);
    cout << "Added successfully to phonebook!" <<endl;
    return 0;
}
