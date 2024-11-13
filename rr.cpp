#include <iostream>
using namespace std;

class process {
public:
    int pid;
    int bt;
    int tat;
    int wt;

    process() {
        pid = 0;
        bt = 0;
        tat = 0;
        wt = 0;
    }

    void getdata() {
        cout << "Enter PID: ";
        cin >> pid;
        cout << "Enter Burst Time: ";
        cin >> bt;
    }

    void display() {
        cout << pid << "\t" << bt << "\t" << tat << "\t" << wt << endl;
    }
};

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    int rem_bt[n];
    cout << "Enter time quantum: ";
    cin >> quantum;

    process p[n];
    for (int i = 0; i < n; i++) {
        p[i].getdata();
    }

    for (int i = 0; i < n; i++) {
        rem_bt[i] = p[i].bt;
    }

    int t = 0, totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (1) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    p[i].wt = t - p[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true) {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        totalWaitingTime += p[i].wt;
        totalTurnaroundTime += p[i].tat;
    }

    double AWT = (double)totalWaitingTime / n;
    double ATAT = (double)totalTurnaroundTime / n;

    cout << "PID\tBT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++) {
        p[i].display();
    }

    cout << "Average Waiting Time: " << AWT << endl;
    cout << "Average Turnaround Time: " << ATAT << endl;

    return 0;
}