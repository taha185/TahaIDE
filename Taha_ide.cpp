#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

// ANSI escape codes for colors and styling
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BG_BLACK "\033[40m"
#define BG_RED   "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_BLUE  "\033[44m"

// Global variables for customization
std::string bgColor = BG_BLACK;
std::string fontColor = WHITE;

// Function to display a loading screen
void showLoadingScreen() {
    std::cout << "Loading TAHA IDE..." << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "[" << std::string(i + 1, '=') << std::string(9 - i, ' ') << "] " << (i + 1) * 10 << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Simulate loading delay
        if (i < 9) std::cout << "\033[1A"; // Move cursor up one line
    }
    std::cout << "\nTAHA IDE is ready!\n" << std::endl;
}

// Function to display the welcome message
void showWelcome() {
    std::cout << bgColor << fontColor;
    std::cout << "=============================================" << std::endl;
    std::cout << "|                                           |" << std::endl;
    std::cout << "|              " << "\033[1;36mTAHA IDE\033[0m" << "                |" << std::endl;
    std::cout << "|                                           |" << std::endl;
    std::cout << "|  A C/C++ IDE with terminal-like features. |" << std::endl;
    std::cout << "|  Write, compile, and run code seamlessly. |" << std::endl;
    std::cout << "|                                           |" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "  Type 'help' for a list of commands." << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << RESET;
}

// Function to display the help message
void showHelp() {
    std::cout << bgColor << fontColor;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  " << GREEN << "help" << fontColor << "       - Show this help message" << std::endl;
    std::cout << "  " << GREEN << "clear" << fontColor << "      - Clear the screen" << std::endl;
    std::cout << "  " << GREEN << "create <file>" << fontColor << " - Create a new file" << std::endl;
    std::cout << "  " << GREEN << "delete <file>" << fontColor << " - Delete a file" << std::endl;
    std::cout << "  " << GREEN << "edit <file>" << fontColor << "   - Open a simple text editor" << std::endl;
    std::cout << "  " << GREEN << "compile <file>" << fontColor << " - Compile a C/C++ file" << std::endl;
    std::cout << "  " << GREEN << "run <file>" << fontColor << "    - Run a compiled program" << std::endl;
    std::cout << "  " << GREEN << "bg <color>" << fontColor << "   - Change background color (black, red, green, blue)" << std::endl;
    std::cout << "  " << GREEN << "font <color>" << fontColor << " - Change font color (red, green, yellow, blue, magenta, cyan, white)" << std::endl;
    std::cout << "  " << GREEN << "Tpkg" << fontColor << "       - Package manager" << std::endl;
    std::cout << "  " << GREEN << "exit" << fontColor << "       - Exit the IDE" << std::endl;
    std::cout << RESET;
}

// Function to clear the screen
void clearScreen() {
    system("cls");
}

// Function to create a file
void createFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file) {
        std::cout << GREEN << "File '" << filename << "' created successfully." << fontColor << std::endl;
    } else {
        std::cerr << RED << "Failed to create file '" << filename << "'." << fontColor << std::endl;
    }
}

// Function to delete a file
void deleteFile(const std::string& filename) {
    if (fs::remove(filename)) {
        std::cout << GREEN << "File '" << filename << "' deleted successfully." << fontColor << std::endl;
    } else {
        std::cerr << RED << "Failed to delete file '" << filename << "'." << fontColor << std::endl;
    }
}

// Simple text editor
void textEditor(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cerr << RED << "Failed to open file '" << filename << "'." << fontColor << std::endl;
        return;
    }

    std::cout << "Editing " << filename << ". Type 'exit' to save and quit." << std::endl;
    std::string line;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, line);
        if (line == "exit") break;
        file << line << std::endl;
    }
    std::cout << GREEN << "File saved." << fontColor << std::endl;
}

// Function to compile a C/C++ file
void compileFile(const std::string& filename) {
    std::string compileCmd = "g++ " + filename + " -o " + filename.substr(0, filename.find_last_of('.'));
    int result = system(compileCmd.c_str());
    if (result == 0) {
        std::cout << GREEN << "File '" << filename << "' compiled successfully." << fontColor << std::endl;
    } else {
        std::cerr << RED << "Failed to compile file '" << filename << "'." << fontColor << std::endl;
    }
}

// Function to run a compiled program
void runProgram(const std::string& filename) {
    std::string runCmd = filename.substr(0, filename.find_last_of('.'));
    int result = system(runCmd.c_str());
    if (result != 0) {
        std::cerr << RED << "Failed to run program '" << runCmd << "'." << fontColor << std::endl;
    }
}

// Function to change background color
void changeBgColor(const std::string& color) {
    if (color == "black") bgColor = BG_BLACK;
    else if (color == "red") bgColor = BG_RED;
    else if (color == "green") bgColor = BG_GREEN;
    else if (color == "blue") bgColor = BG_BLUE;
    else std::cerr << RED << "Invalid background color." << fontColor << std::endl;
    clearScreen();
    showWelcome();
}

// Function to change font color
void changeFontColor(const std::string& color) {
    if (color == "red") fontColor = RED;
    else if (color == "green") fontColor = GREEN;
    else if (color == "yellow") fontColor = YELLOW;
    else if (color == "blue") fontColor = BLUE;
    else if (color == "magenta") fontColor = MAGENTA;
    else if (color == "cyan") fontColor = CYAN;
    else if (color == "white") fontColor = WHITE;
    else std::cerr << RED << "Invalid font color." << fontColor << std::endl;
    clearScreen();
    showWelcome();
}

// Package manager (Tpkg)
void Tpkg() {
    std::cout << "Welcome to " << GREEN << "Tpkg" << fontColor << ", the package manager!" << std::endl;
    std::cout << "Commands: install <package>, remove <package>, list" << std::endl;

    std::string command;
    while (true) {
        std::cout << "Tpkg>> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        } else if (command.find("install ") == 0) {
            std::string package = command.substr(8);
            std::string installCmd = "winget install " + package;
            int result = system(installCmd.c_str());
            if (result == 0) {
                std::cout << GREEN << "Package '" << package << "' installed successfully." << fontColor << std::endl;
            } else {
                std::cerr << RED << "Failed to install package '" << package << "'." << fontColor << std::endl;
            }
        } else if (command.find("remove ") == 0) {
            std::string package = command.substr(7);
            std::string removeCmd = "winget uninstall " + package;
            int result = system(removeCmd.c_str());
            if (result == 0) {
                std::cout << GREEN << "Package '" << package << "' removed successfully." << fontColor << std::endl;
            } else {
                std::cerr << RED << "Failed to remove package '" << package << "'." << fontColor << std::endl;
            }
        } else if (command == "list") {
            system("winget list");
        } else {
            std::cerr << RED << "Invalid Tpkg command." << fontColor << std::endl;
        }
    }
}

int main() {
    // Show loading screen
    showLoadingScreen();

    // Show welcome message
    showWelcome();

    std::string input;
    while (true) {
        std::cout << bgColor << fontColor << ">> " << RESET;
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "Exiting TAHA IDE. Goodbye!" << std::endl;
            break;
        } else if (input == "help") {
            showHelp();
        } else if (input == "clear") {
            clearScreen();
        } else if (input.find("create ") == 0) {
            createFile(input.substr(7));
        } else if (input.find("delete ") == 0) {
            deleteFile(input.substr(7));
        } else if (input.find("edit ") == 0) {
            textEditor(input.substr(5));
        } else if (input.find("compile ") == 0) {
            compileFile(input.substr(8));
        } else if (input.find("run ") == 0) {
            runProgram(input.substr(4));
        } else if (input.find("bg ") == 0) {
            changeBgColor(input.substr(3));
        } else if (input.find("font ") == 0) {
            changeFontColor(input.substr(5));
        } else if (input == "Tpkg") {
            Tpkg();
        } else if (!input.empty()) {
            int result = system(input.c_str());
            if (result != 0) {
                std::cerr << RED << "Command failed with code: " << result << fontColor << std::endl;
            }
        }
    }

    return 0;
}
