#include <iostream>

using namespace std;

struct Process {
    int id;
    int bt;
    int priority;
    int wt;
    int tt;
};

void sortpByPriority(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority < p[j + 1].priority) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter burst time for process " << p[i].id << ": ";
        cin >> p[i].bt;
        cout << "Enter priority for process " << p[i].id << ": ";
        cin >> p[i].priority;
    }

    // Sort p by priority
    sortpByPriority(p, n);

    // Set waiting time and turnaround time for the first process
    p[0].wt = 0;
    p[0].tt = p[0].bt;

    // Calculate waiting time and turnaround time for each process
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tt = p[i].wt + p[i].bt;
    }

    // Calculate average waiting time and turnaround time
    double totalWT = 0, totalTT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTT += p[i].tt;
    }

    double avgWT = totalWT / n;
    double avgTT = totalTT / n;

    // Display results
    cout << "\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t\t" << p[i].bt << "\t\t"
             << p[i].priority << "\t\t" << p[i].wt << "\t\t" << p[i].tt << endl;
    }

    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTT << endl;

    return 0;
}