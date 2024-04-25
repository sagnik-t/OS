#include <iostream>
#include <vector>

using namespace std;

struct Process
{
    int pid, size;
};

struct Block
{
    int id, size;
    bool allocated;
};

class MemoryFitter
{
private:
    int num_blocks, num_processes;
    vector<Process> processes;
    vector<Block> blocks;

public:

    MemoryFitter(int num_blocks, int num_processes) : num_blocks(num_blocks), num_processes(num_processes)
    {
        blocks.resize(num_blocks);
        processes.resize(num_processes);
        this->populate(blocks);
        this->populate(processes);
    }
    void first_fit();
    void best_fit();
    void worst_fit();
    inline void allocate(Process &process, Block &block);
    void populate(vector<Process> &processes);
    void populate(vector<Block> &blocks);
};

void MemoryFitter::populate(vector<Process> &processes)
{
    cout << "Enter process sizes :\n";
    for (int i = 0; i < processes.size(); i++)
    {
        processes[i].pid = i;
        cin >> processes[i].size;
    }
}

void MemoryFitter::populate(vector<Block> &blocks)
{
    cout << "Enter block sizes :\n";
    for (int i = 0; i < blocks.size(); i++)
    {
        blocks[i].id = i;
        cin >> blocks[i].size;
    }
}

inline void MemoryFitter::allocate(Process &process, Block &block)
{
    cout << "Process " << process.pid << ", size " << process.size << " allocated to block " << block.id << ", size " << block.size << endl;
    block.allocated = true;
}

void MemoryFitter::first_fit()
{
    for (auto &process : this->processes)
    {
        for (auto &block : this->blocks)
        {
            if (block.size >= process.size && !block.allocated)
            {
                this->allocate(process, block);
                break;
            }
        }
    }
}

void MemoryFitter::best_fit()
{
    for (auto &process : this->processes)
    {
        int min_diff = __INT32_MAX__;
        Block best_block;
        for (auto &block : this->blocks)
        {
            if (block.size >= process.size && block.size - process.size < min_diff && !block.allocated)
            {
                min_diff = block.size - process.size;
                best_block = block;
            }
        }
        this->allocate(process, best_block);
    }
}

void MemoryFitter::worst_fit()
{
    for (auto &process : this->processes)
    {
        int max_diff = 0;
        Block worst_block;
        for (auto &block : this->blocks)
        {
            if (block.size >= process.size && block.size - process.size > max_diff && !block.allocated)
            {
                max_diff = block.size - process.size;
                worst_block = block;
            }
        }
        this->allocate(process, worst_block);
    }
}

int main()
{
    int num_blocks, num_processes;
    cout <<"Enter number of blocks : ";
    cin >> num_blocks;
    cout <<"Enter number of processes : ";
    cin >> num_processes;

    MemoryFitter memory_fitter(num_blocks, num_processes);
    // memory_fitter.first_fit();
    // memory_fitter.best_fit();
    memory_fitter.worst_fit();

    return 0;
}