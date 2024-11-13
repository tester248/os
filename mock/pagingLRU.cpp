#include <iostream>

using namespace std;

void LRU(int page_reference_string[], int page_reference_string_size, int frame_size) {
    int frames[frame_size];
    int times[frame_size];

    for (int i = 0; i < frame_size; ++i) {
        frames[i] = -1;
        times[i] = -1;
    }

    int page_faults = 0;
    int current_time = 0;

    cout << "LRU Page Replacement Simulation:\n";
    for (int i = 0; i < page_reference_string_size; ++i) {
        int page = page_reference_string[i];
        bool page_found = false;
        int least_used_index = 0;

        for (int j = 0; j < frame_size; ++j) {
            if (frames[j] == page) {
                page_found = true;
                times[j] = current_time;
                break;
            } else if (times[j] < times[least_used_index]) {
                least_used_index = j;
            }
        }

        if (!page_found) {
            frames[least_used_index] = page;
            times[least_used_index] = current_time;
            page_faults++;
            cout << "Page Fault! Replaced page " << frames[least_used_index] << " with page " << page << endl;
        } else {
            cout << "No Page Fault" << endl;
        }

        current_time++;
        for (int j = 0; j < frame_size; ++j) {
            cout << frames[j] << " ";
        }
        cout << endl;
    }

    cout << "Total Page Faults: " << page_faults << endl;
}

void Optimal(int page_reference_string[], int page_reference_string_size, int frame_size) {
    int frames[frame_size];

    for (int i = 0; i < frame_size; ++i) {
        frames[i] = -1;
    }

    int page_faults = 0;

    cout << "Optimal Page Replacement Simulation:\n";
    for (int i = 0; i < page_reference_string_size; ++i) {
        int page = page_reference_string[i];
        bool page_found = false;

        for (int j = 0; j < frame_size; ++j) {
            if (frames[j] == page) {
                page_found = true;
                break;
            }
        }

        if (!page_found) {
            int farthest_future_use = -1;
            int farthest_index = -1;

            for (int j = 0; j < frame_size; ++j) {
                int future_use = -1;
                for (int k = i + 1; k < page_reference_string_size; ++k) {
                    if (frames[j] == page_reference_string[k]) {
                        future_use = k;
                        break;
                    }
                }

                if (future_use == -1) {
                    farthest_index = j;
                    break;
                } else if (future_use > farthest_future_use) {
                    farthest_future_use = future_use;
                    farthest_index = j;
                }
            }

            frames[farthest_index] = page;
            page_faults++;
            cout << "Page Fault! Replaced page " << frames[farthest_index] << " with page " << page << endl;
        } else {
            cout << "No Page Fault" << endl;
        }

        for (int j = 0; j < frame_size; ++j) {
            cout << frames[j] << " ";
        }
        cout << endl;
    }

    cout << "Total Page Faults: " << page_faults << endl;
}

int main() {
    int page_reference_string_size, frame_size;

    cout << "Enter the number of pages: ";
    cin >> page_reference_string_size;

    int page_reference_string[page_reference_string_size];

    cout << "Enter the page reference string: ";
    for (int i = 0; i < page_reference_string_size; ++i) {
        cin >> page_reference_string[i];
    }

    cout << "Enter the number of frames: ";
    cin >> frame_size;

    LRU(page_reference_string, page_reference_string_size, frame_size);
    cout << endl;
    Optimal(page_reference_string, page_reference_string_size, frame_size);

    return 0;
}