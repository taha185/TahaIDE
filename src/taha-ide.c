#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

// Function to set console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to display a loading screen
void loadingScreen() {
    setColor(11); // Light cyan
    printf("Loading Taha185 IDE...\n");
    for (int i = 0; i < 10; i++) {
        printf(".");
        Sleep(200); // Simulate loading delay
    }
    printf("\n");
    setColor(7); // Reset to default color
}

// Function to display an inspirational quote in a rectangle
void displayQuote() {
    const char* quote = "Believe you can and you're halfway there. - Theodore Roosevelt";
    int width = strlen(quote) + 4;
    int height = 5;

    setColor(10); // Green
    // Draw a rectangle
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    // Display the quote
    printf("  %s\n", quote);
    setColor(7); // Reset to default color
}

// Function to create a file
void createFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        setColor(2); // Green
        printf("File created: %s\n", filename);
        fclose(file);
    } else {
        setColor(4); // Red
        printf("Failed to create file: %s\n", filename);
    }
    setColor(7); // Reset to default color
}

// Function to delete a file
void deleteFile(const char* filename) {
    if (remove(filename) == 0) {
        setColor(2); // Green
        printf("File deleted: %s\n", filename);
    } else {
        setColor(4); // Red
        printf("Failed to delete file: %s\n", filename);
    }
    setColor(7); // Reset to default color
}

// Function to create a directory
void createDirectory(const char* dirname) {
    if (_mkdir(dirname) == 0) {
        setColor(2); // Green
        printf("Directory created: %s\n", dirname);
    } else {
        setColor(4); // Red
        printf("Failed to create directory: %s\n", dirname);
    }
    setColor(7); // Reset to default color
}

// Function to delete a directory
void deleteDirectory(const char* dirname) {
    if (_rmdir(dirname) == 0) {
        setColor(2); // Green
        printf("Directory deleted: %s\n", dirname);
    } else {
        setColor(4); // Red
        printf("Failed to delete directory: %s\n", dirname);
    }
    setColor(7); // Reset to default color
}

// Simple text editor
void textEditor(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        setColor(4); // Red
        printf("Failed to open file: %s\n", filename);
        setColor(7); // Reset to default color
        return;
    }

    setColor(11); // Light cyan
    printf("Simple Text Editor (Press Ctrl+Z and Enter to save and exit)\n");
    setColor(7); // Reset to default color

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (feof(stdin)) break; // Exit on Ctrl+Z
        fputs(buffer, file);
    }

    fclose(file);
    setColor(2); // Green
    printf("File saved: %s\n", filename);
    setColor(7); // Reset to default color
}

// Function to compile and run a C/C++ file
void compileAndRun(const char* filename) {
    char command[256];
    setColor(14); // Yellow

    // Check if the file is a C or C++ file
    if (strstr(filename, ".c") != NULL) {
        snprintf(command, sizeof(command), "gcc %s -o %s.exe && %s.exe", filename, filename, filename);
    } else if (strstr(filename, ".cpp") != NULL) {
        snprintf(command, sizeof(command), "g++ %s -o %s.exe && %s.exe", filename, filename, filename);
    } else {
        setColor(4); // Red
        printf("Unsupported file type. Use .c or .cpp files.\n");
        setColor(7); // Reset to default color
        return;
    }

    // Execute the command
    printf("Compiling and running %s...\n", filename);
    int result = system(command);

    if (result == 0) {
        setColor(2); // Green
        printf("Program executed successfully.\n");
    } else {
        setColor(4); // Red
        printf("Compilation or execution failed.\n");
    }
    setColor(7); // Reset to default color
}

// Function to display the help page
void displayHelp() {
    setColor(14); // Yellow
    printf("\nAvailable Commands:\n");
    printf("  create <filename>  - Create a new file\n");
    printf("  delete <filename>  - Delete a file\n");
    printf("  mkdir <dirname>    - Create a new directory\n");
    printf("  rmdir <dirname>    - Delete a directory\n");
    printf("  edit <filename>    - Open a simple text editor\n");
    printf("  compile <filename> - Compile and run a C/C++ file\n");
    printf("  quote              - Display an inspirational quote\n");
    printf("  help               - Show this help page\n");
    printf("  exit               - Exit the program\n");
    setColor(7); // Reset to default color
}

// Main terminal-like interface
void terminal(const char* username) {
    char input[256];
    char prompt[256];
    snprintf(prompt, sizeof(prompt), "taha_ide@%s$ ", username);

    while (1) {
        setColor(9); // Blue
        printf("%s", prompt);
        setColor(7); // Reset to default color

        if (!fgets(input, sizeof(input), stdin)) break;

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) break;
        else if (strncmp(input, "create ", 7) == 0) {
            createFile(input + 7);
        } else if (strncmp(input, "delete ", 7) == 0) {
            deleteFile(input + 7);
        } else if (strncmp(input, "mkdir ", 6) == 0) {
            createDirectory(input + 6);
        } else if (strncmp(input, "rmdir ", 6) == 0) {
            deleteDirectory(input + 6);
        } else if (strncmp(input, "edit ", 5) == 0) {
            textEditor(input + 5);
        } else if (strncmp(input, "compile ", 8) == 0) {
            compileAndRun(input + 8);
        } else if (strcmp(input, "quote") == 0) {
            displayQuote();
        } else if (strcmp(input, "help") == 0) {
            displayHelp();
        } else {
            setColor(4); // Red
            printf("Unknown command: %s\n", input);
            setColor(7); // Reset to default color
        }
    }
}

int main() {
    char username[256];
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    loadingScreen();
    setColor(14); // Yellow
    printf("Welcome to Taha185 IDE, %s!\n", username);
    setColor(7); // Reset to default color

    terminal(username);

    setColor(14); // Yellow
    printf("Thank you for using Taha185 IDE. Goodbye!\n");
    setColor(7); // Reset to default color

    return 0;
}
