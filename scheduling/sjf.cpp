#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

#include "scheduler.cpp"

tuple<float, float> Scheduler::sjf_scheduler()
{
    sort(this->processes.begin(), this->processes.end(), [](const Process &a, const Process &b) {
        return a.burst_time < b.burst_time;
    });

    int curr_time = 0, total_wait = 0, total_turnaround = 0;

    for (auto &process : this->processes)
    {
        this->schedule(process);

        total_wait += curr_time;
        curr_time += process.burst_time;
        total_turnaround += curr_time;
    }

    float avg_wait = static_cast<float>(total_wait) / this->processes.size();
    float avg_turnaround = static_cast<float>(total_turnaround) / this->processes.size();

    return make_tuple(avg_wait, avg_turnaround);
}

int main()
{
    Scheduler scheduler;
    scheduler.populate();

    auto [avg_wait, avg_turnaround] = scheduler.sjf_scheduler();

    scheduler.display();

    cout << "Average waiting time: " << avg_wait << endl;
    cout << "Average turnaround time: " << avg_turnaround << endl;

    return 0;
}