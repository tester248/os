    #include <iostream>
    using namespace std;

    const int P = 5; // Number of processes
    const int R = 3; // Number of resources

    void calculateNeed(int need[P][R], int max[P][R], int alloc[P][R]) {
        for (int i = 0; i < P; i++)
            for (int j = 0; j < R; j++)
                need[i][j] = max[i][j] - alloc[i][j];
    }

    bool isSafe(int processes[], int avail[], int max[][R], int alloc[][R]) {
        int need[P][R];
        calculateNeed(need, max, alloc);

        bool finish[P] = {0};
        int safeSeq[P];
        int work[R];
        for (int i = 0; i < R; i++)
            work[i] = avail[i];

        int count = 0;
        while (count < P) {
            bool found = false;
            for (int p = 0; p < P; p++) {
                if (finish[p] == 0) {
                    int j;
                    for (j = 0; j < R; j++)
                        if (need[p][j] > work[j])
                            break;

                    if (j == R) {
                        for (int k = 0; k < R; k++)
                            work[k] += alloc[p][k];
                        safeSeq[count++] = p;
                        finish[p] = 1;
                        found = true;
                    }
                }
            }

            if (!found) {
                cout << "System is not in a safe state.\n";
                return false;
            }
        }

        cout << "System is in a safe state.\nSafe sequence is: ";
        for (int i = 0; i < P; i++) {
            cout << "P" << safeSeq[i];
            if (i != P - 1)
                cout << " -> ";
        }
        cout << endl;

        return true;
    }

    int main() {
        int processes[] = {0, 1, 2, 3, 4};
        
        int avail[R]; 
        cout << "Enter available resources (space-separated): ";
        for (int i = 0; i < R; i++) {
            cin >> avail[i];
        }

        int max[P][R], alloc[P][R];

        cout << "Enter maximum resource needs for each process (5 processes, 3 resources):\n";
        for (int i = 0; i < P; i++) {
            cout << "Process " << i << ": ";
            for (int j = 0; j < R; j++) {
                cin >> max[i][j];
            }
        }

        cout << "Enter allocated resources for each process (5 processes, 3 resources):\n";
        for (int i = 0; i < P; i++) {
            cout << "Process " << i << ": ";
            for (int j = 0; j < R; j++) {
                cin >> alloc[i][j];
            }
        }

        isSafe(processes, avail, max, alloc);
        return 0;
    }
