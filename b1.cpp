#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = fork(); // Create a child process

    if (pid == -1) {
        // If fork failed
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        cout << "Child process running..." << endl;
        execlp("/bin/ps", "ps", "-f", NULL); // Execute the 'ps' command
        // If execlp() fails
        cerr << "Failed to execute ps!" << endl;
        return 1;
    } else {
        // Parent process
        cout << "Parent process waiting for child..." << endl;
        wait(NULL); // Wait for the child process to complete
        cout << "Child process completed." << endl;
    }

    return 0;
}
