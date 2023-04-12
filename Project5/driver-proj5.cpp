#include <iostream>
#include "process-proj5.h"
#include "arrayheap-prof-proj5.h"
#include "arrayheap-student-proj5.h"

using namespace std;

int main()
{
    int numProcesses;
    int currTime = 0;
    int numRun = 0;
    int numSkipped = 0;
    ArrayHeap<Process> heap;
    Process currProcess;
    Process *nextProcess = new Process(0);
    cin >> numProcesses;
    cin >> *nextProcess;
    bool noInput = false;

    while (numRun + numSkipped < numProcesses)
    {
        
        while (nextProcess->getSubmissionTime() <= currTime && !noInput)
        {
            heap.insert(*nextProcess);
            nextProcess = new Process(nextProcess->getId() + 1);
            if (!(cin >> *nextProcess))
            {
                noInput = true;
            }
            
        }

        if (heap.getNumItems() == 0)
        {
            currTime++;
        }
        else
        {
            currProcess = heap.getMinItem();
            heap.removeMinItem();
            if (currProcess.canComplete(currTime))
            {
                currTime = currProcess.run(currTime);
                numRun++;
            }
            else
            {
                numSkipped++;
                cout << "skipping process id " << currProcess.getId() << " at " << currTime << endl;
                currTime++;
            }
        }
    }

    cout << "final clock is                 " << currTime << endl;
    cout << "number of processes run is     " << numRun << endl;
    cout << "number of processes skipped is " << numSkipped << endl;

    return 0;
}