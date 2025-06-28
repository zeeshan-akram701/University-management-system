#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <string>
using namespace std;
void getPassword(string &password) {
    struct termios oldt, newt;
    char ch;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable echoing
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Prompt for password
    cout << "Enter password: ";
    while (std::cin.get(ch) && ch != '\n') {
        password += ch;
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
   cout << std::endl;
}

int main() {
    std::string password;
    getPassword(password);
    std::cout << "You entered: " << password << std::endl; // For testing only, remove in real applications.
    return 0;
}
