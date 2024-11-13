#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

#define BUFFER_SIZE 1024

int main() {
    int pipefds1[2]; // Pipe for parent to child communication
    int pipefds2[2]; // Pipe for child to parent communication
    pid_t pid;
    char filepath[BUFFER_SIZE] = "./file.txt"; 
    char readmessage[BUFFER_SIZE];

    // Create pipes
    if (pipe(pipefds1) == -1) {
        perror("Unable to create pipe 1");
        return 1;
    }
    if (pipe(pipefds2) == -1) {
        perror("Unable to create pipe 2");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent process
        close(pipefds1[0]); // Close reading end of pipe 1
        close(pipefds2[1]); // Close writing end of pipe 2

        // Write the pathname of the file to the child
        cout << "In Parent Process: Writing to pipe1 - File path is: " << filepath << endl;
        write(pipefds1[1], filepath, strlen(filepath) + 1);

        // Read contents from child
        read(pipefds2[0], readmessage, BUFFER_SIZE);
        cout << "In Parent Process: Reading from pipe2 - File contents are:\n" << readmessage << endl;

        close(pipefds1[1]); // Close writing end of pipe 1
        close(pipefds2[0]); // Close reading end of pipe 2
    } else { // Child process
        close(pipefds1[1]); // Close writing end of pipe 1
        close(pipefds2[0]); // Close reading end of pipe 2

        // Read the file path from the parent
        read(pipefds1[0], readmessage, BUFFER_SIZE);
        cout << "In Child Process: Reading from pipe1 - File path is: " << readmessage << endl;

        // Open the file and read its contents
        FILE* file = fopen(readmessage, "r");
        if (file == nullptr) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        // Read the file contents
        char fileContent[BUFFER_SIZE];
        fread(fileContent, sizeof(char), BUFFER_SIZE, file);
        fclose(file);

        // Write the file contents back to the parent
        write(pipefds2[1], fileContent, strlen(fileContent) + 1);
        cout << "In Child Process: Writing to pipe2 - File contents sent.\n";

        close(pipefds1[0]); // Close reading end of pipe 1
        close(pipefds2[1]); // Close writing end of pipe 2
        exit(EXIT_SUCCESS);
    }

    return 0;
}
