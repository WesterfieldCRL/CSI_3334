/* CSI 3334
 * Project 5 -- 
 * Filename: driver-proj5.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This program reads in a list of processes from standard input and runs them
 * using a heap to determine which process to run next. The program will run
 * processes in the order of their deadlines, and if two processes have the
 * same deadline, the process with the shortest required time will be run
 * first. If two processes have the same deadline and required time, the
 * process with the lowest id will be run first. The program will run until
 * all processes have been run or skipped. Processes are only read inserted
 * into the heap when their submission time is less than or equal to the
 * current system time. If the heap is empty, the system time is incremented.
 */

#include <iostream>
#include "process-proj5.h"
#include "arrayheap-prof-proj5.h"
#include "arrayheap-student-proj5.h"

using namespace std;

/**
 * main
 *
 * This function reads in a list of processes from standard input and runs
 * them using a heap to determine which process to run next. The program will
 * run processes in order. The program will run until all processes have been
 * run or skipped. Processes are only read inserted into the heap when their
 * submission time is less than or equal to the current system time. If the
 * heap is empty, the system time is incremented. The program will print the
 * final clock, the number of processes run, and the number of processes
 * skipped.
 * 
 * Parameters:
 *   none
 * 
 * Return value: 0 (indicating a successful run)
 */

int main() {
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

    while (numRun + numSkipped < numProcesses) {
        
        while (nextProcess->getSubmissionTime() <= currTime && !noInput) {
            heap.insert(*nextProcess);
            delete nextProcess;
            nextProcess = new Process(nextProcess->getId() + 1);
            if (!(cin >> *nextProcess)) {
                noInput = true;
            }
            
        }

        if (heap.getNumItems() == 0) {
            currTime++;
        }
        else {
            currProcess = heap.getMinItem();
            heap.removeMinItem();
            if (currProcess.canComplete(currTime)) {
                currTime = currProcess.run(currTime);
                numRun++;
            }
            else {
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