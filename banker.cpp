#include <iostream>
#include <vector>
using namespace std;

class Bankers
{
private:
    int num_processes, num_rscs;
    vector<vector<int>> allocated, requested;
    vector<int> available;

public:

    Bankers(int num_processes, int num_rscs) : num_processes(num_processes), num_rscs(num_rscs)
    {
        allocated.resize(num_processes, vector<int>(num_rscs));
        requested.resize(num_processes, vector<int>(num_rscs));
        available.resize(num_rscs);
        populate(allocated);
        populate(requested);
        populate(available);
    }

    void populate(vector<vector<int>> &matrix);
    void populate(vector<int> &v);
    bool solve();
};

void populate(vector<vector<int>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cin >> matrix[i][j];
        }
    }
}

void populate(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cin >> v[i];
    }
}

bool Bankers::solve()
{
    vector<int> work = available;
    vector<bool> completed(num_processes, false);
    vector<int> safe_sequence;
    int count = 0;

    while (count < num_processes)
    {
        bool found = false;
        for (int i = 0; i < num_processes; i++)
        {
            if (!completed[i])
            {
                int j;
                for (j = 0; j < num_rscs; j++)
                {
                    if (requested[i][j] > work[j])
                        break;
                }

                if (j == num_rscs)
                {
                    for (j = 0; j < num_rscs; j++)
                    {
                        work[j] += allocated[i][j];
                    }
                    safe_sequence.push_back(i);
                    completed[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found)
        {
            cout << "System is not in safe state\n";
            return false;
        }
    }

    cout << "System is in safe state\n";
    cout << "Safe sequence: ";
    for (int i = 0; i < safe_sequence.size(); i++)
    {
        cout << safe_sequence[i] << " ";
    }
    cout << endl;

    return true;
}