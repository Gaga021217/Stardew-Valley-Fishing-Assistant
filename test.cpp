#include <iostream>
#include <termios.h>
#include <unistd.h>

const int NUM_OPTIONS = 3;
const std::string options[NUM_OPTIONS] = {"Option 1", "Option 2", "Option 3"};

void printOptions(int selectedOption) {
    // ANSI escape codes for colors
    const std::string selectedColor = "\033[1;32m"; // Green for selected option
    const std::string defaultColor = "\033[0m"; // Default color

    system("clear"); // Clear screen

    for (int i = 0; i < NUM_OPTIONS; ++i) {
        if (i == selectedOption) {
            std::cout << selectedColor << "> " << options[i] << defaultColor << std::endl; // Highlight selected option
        } else {
            std::cout << "  " << options[i] << std::endl;
        }
    }
}

// Function to enable non-blocking input
void setNonBlocking(bool enable) {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    if (enable) {
        ttystate.c_lflag &= ~ICANON; // Disable canonical mode
        ttystate.c_cc[VMIN] = 1; // Minimum number of characters to read
    } else {
        ttystate.c_lflag |= ICANON; // Enable canonical mode
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int main() {
    int selectedOption = 0;
    printOptions(selectedOption);

    setNonBlocking(true); // Enable non-blocking input

    char key;
    do {
        key = getchar(); // Read a single character (non-blocking)

        // Handle arrow key presses
        switch (key) {
            case 65: // Up arrow key
                if (selectedOption > 0) {
                    selectedOption--;
                }
                break;
            case 66: // Down arrow key
                if (selectedOption < NUM_OPTIONS - 1) {
                    selectedOption++;
                }
                break;
        }
        printOptions(selectedOption);
    } while (key != 10); // Repeat until Enter key is pressed

    setNonBlocking(false); // Disable non-blocking input

    std::cout << "Selected option: " << options[selectedOption] << std::endl;

    return 0;
}