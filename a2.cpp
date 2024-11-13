#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5;
const int NUM_ITEMS = 10;

vector<int> buffer(BUFFER_SIZE);
int in = 0; // Next empty slot
int out = 0; // Next full slot
mutex mtx;
condition_variable empty, full;

void producer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100; // Produce an item
        {
            unique_lock<mutex> lock(mtx);
            // Wait until there's an empty slot
            empty.wait(lock, [] { return (in - out + BUFFER_SIZE) % BUFFER_SIZE < BUFFER_SIZE - 1; });
            buffer[in] = item;
            cout << "Produced: " << item << endl;
            in = (in + 1) % BUFFER_SIZE;
        }
        full.notify_one(); // Notify the consumer
        this_thread::sleep_for(chrono::milliseconds(rand() % 100));
    }
}

void consumer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item;
        {
            unique_lock<mutex> lock(mtx);
            // Wait until there's an item to consume
            full.wait(lock, [] { return in != out; });
            item = buffer[out];
            cout << "Consumed: " << item << endl;
            out = (out + 1) % BUFFER_SIZE;
        }
        empty.notify_one(); // Notify the producer
        this_thread::sleep_for(chrono::milliseconds(rand() % 100));
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator
    thread prod(producer);
    thread cons(consumer);
    prod.join();
    cons.join();
    return 0;
}
