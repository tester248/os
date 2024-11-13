#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits> // Include climits for INT_MAX
using namespace std;

// Function to find if there is a page hit
bool pageHit(vector<int> &frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end();
}

// FIFO Page Replacement
void FIFO(vector<int> &pages, int capacity) {
    vector<int> frames;
    int pageFaults = 0;
    
    for (int i = 0; i < pages.size(); i++) {
        if (!pageHit(frames, pages[i])) {
            if (frames.size() == capacity)
                frames.erase(frames.begin());
            frames.push_back(pages[i]);
            pageFaults++;
        }
        cout << "Page " << pages[i] << " -> ";
        for (int frame : frames)
            cout << frame << " ";
        cout << "\n";
    }
    cout << "FIFO Page Faults: " << pageFaults << "\n";
}

// LRU Page Replacement
void LRU(vector<int> &pages, int capacity) {
    vector<int> frames;
    unordered_map<int, int> indices;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (!pageHit(frames, pages[i])) {
            if (frames.size() == capacity) {
                int lru = INT_MAX, lruIndex = -1;
                for (int j = 0; j < frames.size(); j++) {
                    if (indices[frames[j]] < lru) {
                        lru = indices[frames[j]];
                        lruIndex = j;
                    }
                }
                frames[lruIndex] = pages[i];
            } else {
                frames.push_back(pages[i]);
            }
            pageFaults++;
        }
        indices[pages[i]] = i;
        cout << "Page " << pages[i] << " -> ";
        for (int frame : frames)
            cout << frame << " ";
        cout << "\n";
    }
    cout << "LRU Page Faults: " << pageFaults << "\n";
}

// Optimal Page Replacement
void optimal(vector<int> &pages, int capacity) {
    vector<int> frames;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (!pageHit(frames, pages[i])) {
            if (frames.size() == capacity) {
                int farthest = i + 1, replaceIndex = -1;
                for (int j = 0; j < frames.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == frames[j])
                            break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                }
                if (replaceIndex != -1)
                    frames[replaceIndex] = pages[i];
                else
                    frames[0] = pages[i];
            } else {
                frames.push_back(pages[i]);
            }
            pageFaults++;
        }
        cout << "Page " << pages[i] << " -> ";
        for (int frame : frames)
            cout << frame << " ";
        cout << "\n";
    }
    cout << "Optimal Page Faults: " << pageFaults << "\n";
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int capacity = 3;

    cout << "FIFO Page Replacement:\n";
    FIFO(pages, capacity);
    cout << "\nLRU Page Replacement:\n";
    LRU(pages, capacity);
    cout << "\nOptimal Page Replacement:\n";
    optimal(pages, capacity);

    return 0;
}
