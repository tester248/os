#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

using namespace std;

class ReaderWriter {
private:
    mutex mtx;
    condition_variable read_cv, write_cv;
    int read_count = 0;  // Number of active readers
    bool writer_present = false;  // Is a writer present?

public:
    void start_read() {
        unique_lock<mutex> lock(mtx);
        // Wait until no writer is present
        write_cv.wait(lock, [this] { return !writer_present; });
        read_count++;
    }

    void end_read() {
        unique_lock<mutex> lock(mtx);
        read_count--;
        // If no readers are left, notify writers
        if (read_count == 0) {
            write_cv.notify_one();
        }
    }

    void start_write() {
        unique_lock<mutex> lock(mtx);
        // Wait until no readers are present and no writer is present
        write_cv.wait(lock, [this] { return read_count == 0 && !writer_present; });
        writer_present = true;
    }

    void end_write() {
        unique_lock<mutex> lock(mtx);
        writer_present = false;
        // Notify readers and writers
        read_cv.notify_all();
        write_cv.notify_one();
    }
};

void reader(ReaderWriter& rw, int id) {
    rw.start_read();
    cout << "Reader " << id << " is reading." << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    cout << "Reader " << id << " finished reading." << endl;
    rw.end_read();
}

void writer(ReaderWriter& rw, int id) {
    rw.start_write();
    cout << "Writer " << id << " is writing." << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    cout << "Writer " << id << " finished writing." << endl;
    rw.end_write();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    ReaderWriter rw;
    thread readers[2], writers[1];

    // Create reader threads
    for (int i = 0; i < 2; i++) {
        readers[i] = thread(reader, ref(rw), i);
    }

    // Create a single writer thread
    writers[0] = thread(writer, ref(rw), 0);

    // Join all threads
    for (auto& r : readers) r.join();
    for (auto& w : writers) w.join();

    return 0;
}
