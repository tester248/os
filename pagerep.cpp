#include <iostream>
#include <algorithm>

using namespace std;

class PageReplacement {
public:
    void FIFO(const int* pages, int numPages, int frameCount) {
        int pageFaults = 0;
        int frames[frameCount];
        int front = 0;

        for (int i = 0; i < numPages; i++) {
            int page = pages[i];
            bool found = false;

            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == page) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                frames[front] = page;
                front = (front + 1) % frameCount;
                pageFaults++;
            }
        }

        cout << "FIFO Page Faults: " << pageFaults << endl;
    }

    void LRU(const int* pages, int numPages, int frameCount) {
        int pageFaults = 0;
        int frames[frameCount];
        int times[frameCount];

        for (int i = 0; i < frameCount; i++) {
            times[i] = -1;
        }

        int current_time = 0;

        for (int i = 0; i < numPages; i++) {
            int page = pages[i];
            bool found = false;
            int least_used_index = 0;

            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == page) {
                    found = true;
                    times[j] = current_time;
                    break;
                } else if (times[j] < times[least_used_index]) {
                    least_used_index = j;
                }
            }

            if (!found) {
                frames[least_used_index] = page;
                times[least_used_index] = current_time;
                pageFaults++;
            }

            current_time++;
        }

        cout << "LRU Page Faults: " << pageFaults << endl;
    }

    void Optimal(const int* pages, int numPages, int frameCount) {
        int pageFaults = 0;
        int frames[frameCount];

        for (int i = 0; i < frameCount; i++) {
            frames[i] = -1;
        }

        for (int i = 0; i < numPages; i++) {
            int page = pages[i];
            bool found = false;

            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == page) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                int farthest = -1, farthest_index = -1;

                for (int j = 0; j < frameCount; j++) {
                    int next_use = -1;

                    for (int k = i + 1; k < numPages; k++) {
                        if (frames[j] == pages[k]) {
                            next_use = k;
                            break;
                        }
                    }

                    if (next_use == -1) {
                        farthest_index = j;
                        break;
                    } else if (next_use > farthest) {
                        farthest = next_use;
                        farthest_index = j;
                    }
                }

                frames[farthest_index] = page;
                pageFaults++;
            }
        }

        cout << "Optimal Page Faults: " << pageFaults << endl;
    }
};

int main() {
    PageReplacement pr;

    // Input number of pages
    int numPages;
    cout << "Enter the number of pages: ";
    cin >> numPages;

    // Input page reference string
    int* pages = new int[numPages];
    cout << "Enter the page reference string (space-separated): ";
    for (int i = 0; i < numPages; i++) {
        cin >> pages[i];
    }

    // Input number of frames
    int frameCount;
    cout << "Enter the number of frames: ";
    cin >> frameCount;

    // Run the page replacement algorithms
    pr.FIFO(pages, numPages, frameCount);
    pr.LRU(pages, numPages, frameCount);
    pr.Optimal(pages, numPages, frameCount);

    // Clean up dynamic memory
    delete[] pages;

    return 0;
}
