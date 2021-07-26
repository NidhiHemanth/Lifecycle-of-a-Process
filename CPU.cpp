//
//  CPU.cpp
//

#include <iostream>
#include <string>
#include <stddef.h>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

#include "CPU.h"

using namespace std;

//add process to ready queue
void CPU::addProcessToReadyQueue(int priority, int gpid){

    try {
        //check if the new process is higher than the process running in CPU
        if(priority > current_process_in_CPU_priority){
        
            if(current_process_in_CPU_priority == -1){  //when CPU is empty
                current_process_in_CPU_priority = priority;
                current_process_in_CPU_pid = gpid;
                // denotes that the new process will be executed in the CPU
            }
            else{  
                //when CPU has process and and need to push back the old one
                
                if(current_process_in_CPU_priority == 3)
                    readyQueuePrior3.push_back(current_process_in_CPU_pid);
                else if(current_process_in_CPU_priority == 2)
                    readyQueuePrior2.push_back(current_process_in_CPU_pid);
                else if(current_process_in_CPU_priority == 1)
                    readyQueuePrior1.push_back(current_process_in_CPU_pid);
                else if(current_process_in_CPU_priority == 0)
                    readyQueuePrior0.push_back(current_process_in_CPU_pid);
                else
                    throw "Cannot push back the process that was running in CPU!";
            
                current_process_in_CPU_priority = priority;
                current_process_in_CPU_pid = gpid;
            }
        
        }
        
        else{

            if(priority == 4)
                readyQueuePrior4.push_back(gpid);
            else if(priority == 3)
                readyQueuePrior3.push_back(gpid);
            else if(priority == 2)
                readyQueuePrior2.push_back(gpid);
            else if(priority == 1)
                readyQueuePrior1.push_back(gpid);
            else if(priority == 0)
                readyQueuePrior0.push_back(gpid);
            else 
                throw "Cannot add process to Ready Queue.";
             
        }

    } catch (char const* error_message) {
        cout << "\t*Error; " << error_message << endl;
    }
    
}

//remove process from CPU when terminate
void CPU::removeProcessfromCPU() {
    
    // we do this since CPU will be idle since we are removing the currently running process
    current_process_in_CPU_priority = -1;
    current_process_in_CPU_pid = -1;
    
    //push the highest priority process in CPU
    //since CPU shouldn't be idle
    //FCFS is used to schedule
    if(!readyQueuePrior4.empty()){
        current_process_in_CPU_priority = 4;
        current_process_in_CPU_pid = readyQueuePrior4.front();
        readyQueuePrior4.pop_front();
    }
    else if(!readyQueuePrior3.empty()){
        current_process_in_CPU_priority = 3;
        current_process_in_CPU_pid = readyQueuePrior3.front();
        readyQueuePrior3.pop_front();
    }
    else if(!readyQueuePrior2.empty()){
        current_process_in_CPU_priority = 2;
        current_process_in_CPU_pid = readyQueuePrior2.front();
        readyQueuePrior2.pop_front();
    }
    else if(!readyQueuePrior1.empty()){
        current_process_in_CPU_priority = 1;
        current_process_in_CPU_pid = readyQueuePrior1.front();
        readyQueuePrior1.pop_front();
    }
    else if(!readyQueuePrior0.empty()){
        current_process_in_CPU_priority = 0;
        current_process_in_CPU_pid = readyQueuePrior0.front();
        readyQueuePrior0.pop_front();
    }
    
}

//command - S r
void CPU::commandShowReadyQueueAndCPU(){
    
    if(current_process_in_CPU_pid == -1)
        cout << "\tNo process in CPU" << endl;
    else
        cout << "\tIn CPU: P" << current_process_in_CPU_pid<< endl;
    
    if(!readyQueuePrior4.empty()){
        cout << "\tReady Queue Priority 4: ";
        for (list<int>::iterator it = readyQueuePrior4.begin(); it !=readyQueuePrior4.end(); ++it)
            cout << "P" << *it << " ";
        cout << endl;
    }
    if(!readyQueuePrior3.empty()){
        cout << "\tReady Queue Priority 3: ";
        for (list<int>::iterator it = readyQueuePrior3.begin(); it !=readyQueuePrior3.end(); ++it)
            cout << "P" << *it << " ";
        cout << endl;
    }
    if(!readyQueuePrior2.empty()){
        cout << "\tReady Queue Priority 2: ";
        for (list<int>::iterator it = readyQueuePrior2.begin(); it !=readyQueuePrior2.end(); ++it)
            cout << "P" << *it << " ";
        cout << endl;
    }
    if(!readyQueuePrior1.empty()){
        cout << "\tReady Queue Priority 1: ";
        for (list<int>::iterator it = readyQueuePrior1.begin(); it !=readyQueuePrior1.end(); ++it)
            cout << "P" << *it << " ";
        cout << endl;
    }
    if(!readyQueuePrior0.empty()){
        cout << "\tReady Queue Priority 0: ";
        for (list<int>::iterator it = readyQueuePrior0.begin(); it !=readyQueuePrior0.end(); ++it)
            cout << "P" << *it << " ";
        cout << endl;
    }
    
}