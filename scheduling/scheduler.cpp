#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

#include "process.cpp"

using namespace std;

class Scheduler
{
private:
    vector<Process> processes;
    queue<Process> scheduled_processes;
    bool priority_based = false;

public:
    explicit Scheduler() = default;

    Scheduler(bool priority_based) : priority_based(priority_based) {}

    tuple<float, float> fcfs_scheduler();
    tuple<float, float> sjf_scheduler();
    tuple<float, float> priority_scheduler();
    tuple<float, float> round_robin_scheduler();

    inline void schedule(const Process &process)
    {
        scheduled_processes.push(process);
    }

    void populate()
    {
        int n;
        cout << "Enter the number of processes: ";
        cin >> n;

        cout << "Enter the arrival time and burst time of each process:\n";
        for (int i = 0; i < n; i++)
        {
            int burst_time, priority;
            cout << "Burst time of process " << i + 1 << ": ";
            cin >> burst_time;
            if (this->priority_based)
            {
                cout << "Priority of process " << i + 1 <<": ";
                cin >> priority;
            }
            processes.push_back(Process(i, burst_time, priority));
        }
    }
    
    void display()
    {
        cout << "pid\t" << "burst_time\n";
        while (!this->scheduled_processes.empty())
        {
            Process process = this->scheduled_processes.front();
            process.display();
            cout << endl;
            this->scheduled_processes.pop();
        }
    }
};