#include <iostream>
#include <vector>

struct Process
{
    unsigned int pid, burst_time;
    int priority;

    Process(int pid, int burst_time, int priority = -1) : pid(pid), burst_time(burst_time), priority(priority) {}

    inline void display() const
    {
        std::cout << this->pid << "\t" << this->burst_time;
    }
};
