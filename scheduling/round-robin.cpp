#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

#include "scheduler.cpp"

using namespace std;

tuple<float, float> Scheduler::round_robin_scheduler()
{
    int quantum;
    cout << "Enter the quantum: ";
    cin >> quantum;

    queue<Process> ready_queue;
    int curr_time = 0, total_wait = 0, total_turnaround = 0;

    for (auto &process : this->processes)
        ready_queue.push(process);
    
    while (!ready_queue.empty())
    {
        Process process = ready_queue.front();
        ready_queue.pop();
        this->schedule(process);

        if (process.burst_time > quantum)
        {
            process.burst_time -= quantum;
            curr_time += quantum;
            ready_queue.push(process);
        }
        else
        {
            curr_time += process.burst_time;
            total_wait += curr_time - process.burst_time;
            total_turnaround += curr_time;
        }
    }

    float avg_wait = static_cast<float>(total_wait) / this->processes.size();
    float avg_turnaround = static_cast<float>(total_turnaround) / this->processes.size();

    return make_tuple(avg_wait, avg_turnaround);
}

int main()
{
    Scheduler scheduler;
    scheduler.populate();

    auto [avg_wait, avg_turnaround] = scheduler.round_robin_scheduler();

    scheduler.display();

    cout << "Average waiting time: " << avg_wait << endl;
    cout << "Average turnaround time: " << avg_turnaround << endl;

    return 0;
}