#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

int readers_count = 0; // Number of active readers
mutex resource_mutex; // Controls access to the shared resource
mutex readers_count_mutex; // Protects access to readers_count
condition_variable resource_cv; // Notifies writers when the resource is free

// Function for reader
void reader(int id) {
    while (true) {
        // Lock to update readers count
        {
            unique_lock<mutex> lock(readers_count_mutex);
            readers_count++;
            if (readers_count == 1) {
                resource_mutex.lock(); // First reader locks the resource
            }
        }

        // Reading section
        cout << "Reader " << id << " is reading.\n";
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate reading time

        // Unlock to update readers count
        {
            unique_lock<mutex> lock(readers_count_mutex);
            readers_count--;
            if (readers_count == 0) {
                resource_mutex.unlock(); // Last reader unlocks the resource
            }
        }

        // Sleep before trying to read again
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

// Function for writer
void writer(int id) {
    while (true) {
        // Wait until the resource is available
        unique_lock<mutex> lock(resource_mutex);

        // Writing section
        cout << "Writer " << id << " is writing.\n";
        this_thread::sleep_for(chrono::milliseconds(150)); // Simulate writing time

        // Sleep before trying to write again
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    // Create reader and writer threads
    thread readers[] = {thread(reader, 1), thread(reader, 2), thread(reader, 3)};
    thread writers[] = {thread(writer, 1), thread(writer, 2)};

    // Join threads (in a real-world application, they would run indefinitely)
    for (auto& r : readers) r.join();
    for (auto& w : writers) w.join();

    return 0;
}
