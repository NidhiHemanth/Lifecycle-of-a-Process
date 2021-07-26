//
//  CPU.h
//

#include <iostream>
#include <list>

#pragma once
// cause the current source file to be included only once in a single compilation.

class CPU
{
    
public:
    int current_process_in_CPU_priority = -1;
    int current_process_in_CPU_pid = -1;
    
    // restricted readyQueue length to 5 for simplicity
    std::list<int> readyQueuePrior4;
    std::list<int> readyQueuePrior3;
    std::list<int> readyQueuePrior2;
    std::list<int> readyQueuePrior1;
    std::list<int> readyQueuePrior0;
    
    // function to add a new process to ready queue
    void addProcessToReadyQueue(int priority, int gpid);
    
    // display processes in the ready queue
    // command - S r
    void commandShowReadyQueueAndCPU();
    
    // remove a process from the ready queue, hence the CPU
    void removeProcessfromCPU();
};