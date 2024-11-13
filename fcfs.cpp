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
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    process p[n];
    for (int i = 0; i < n; i++) {
        p[i].getdata();
    }

    int waitingTime = 0, totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        p[i].wt = waitingTime;
        waitingTime += p[i].bt;
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