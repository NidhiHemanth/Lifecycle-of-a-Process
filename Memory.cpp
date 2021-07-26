//
//  Memory.cpp
//

#include <iostream>
#include <string>
#include <stddef.h>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

#include "IO.h"
#include "Memory.h"

using namespace std;

//check if there is a hole in memory that is bigger than the size of the new process
Memory::PCB* Memory::findHole(double size){
    
    PCB* current = head;
    
    // assuming it's variable sized partitioning
    while(current != tail){
        
        // if we find a hole big enough to fit the process
        //  | current |_____| current->next |
        if(((current->next->begin) - (current->end)) > size)
            return current;
        
        current = current -> next;

    }

    return NULL;

}

//find pid in memory
Memory::PCB* Memory::findPidInMem(int wantPid){
    
    PCB* check = head;
    
    while(check != tail){
        if(check->pid == wantPid)
            return check;
        
        check = check -> next;
    }

    return NULL;

}

//command - A <priority> <size>
//used to add a newly created process into the memory 
//PCB allocated & pushed into ready queue if CPU not idle
void Memory::commandAdd(int priority, double size){

    PCB* firstNode = NULL;
    PCB* newNode;
    PCB* nextNode;
    PCB* limitNode;
    
    //create first (dummy) node if memory is empty
    if(head == NULL){
        firstNode = new PCB;
        firstNode -> end = -1;   
        
        head = firstNode;        // dummy head
    }
    
    newNode = new PCB;
    newNode -> pid = ++gpid;     // what is gpid?
    newNode -> priority = priority;
    
    addProcessToReadyQueue(priority, newNode -> pid);
    
    // for the firstly created process
    if(gpid == 1){ 
        
        //create first node
        newNode -> begin = 0;
        newNode -> end = size -1;

        newNode -> prev = firstNode; // head 
        firstNode -> next = newNode;
        
        //add limit/last node (dummy) node
        limitNode = new PCB;
        limitNode -> begin = size_of_memory;

        newNode -> next = limitNode;
        limitNode -> prev = newNode;
        
        tail = limitNode;         // dummy tail

    }
    else{

        PCB* node = findHole(size);

        try {
            // if there is no hole
            if(node == NULL)
                throw "There is no enough space in Memory!";
            else{
                // insert in the middle (in the hole)
                nextNode = node -> next;
                newNode -> next = nextNode;
                newNode -> prev = node;
                node -> next = newNode;
                nextNode -> prev = newNode;

                newNode -> begin = newNode -> prev -> end +1;
                newNode -> end = newNode -> begin + size -1;
            }
        } catch (char const* error_message) {
            cout << "*Error; " << error_message << endl;
        }
        
    }
}

//command - t
void Memory::commandTerminate(){
    
    //remove the process from memory
    removeProcessFromMem();
    //remove from CPU
    removeProcessfromCPU();
    
}

//remove process from Mem when terminate
void Memory::removeProcessFromMem(){

    PCB* current;
    PCB* sucNode;
    PCB* preNode;
    
    current = head;
    
    try {

        if(current->next == tail)
            throw "No process in memory";
            
        while(current -> pid != current_process_in_CPU_pid){
            current = current -> next;
        }
        sucNode = current -> next;
        preNode = current -> prev;
        
        sucNode -> prev = preNode;

        // if(preNode != 0)
        if(preNode != NULL)
            preNode -> next = sucNode;
        if(current == head)
            head = sucNode;

    } catch (char const* error_message) {
        cout << "\t*Error; " << error_message << endl;
    }
    
    //delete head;
}

//command - D #
void Memory::commandFinishWorkHardDisk(int num){
    
    PCB* temp;
    
    try {

        if(hardDisks[num-1].empty()) 
            throw "Hard Drive is idle";

        if(!hardDisks[num-1].empty()){
            temp = findPidInMem(hardDisks[num-1].front());
            if(temp == NULL){
                // in cases when process was removed from memory
                throw "Didn't find the pid in Memory";
            }
            else{
                addProcessToReadyQueue(temp->priority , hardDisks[num-1].front());
                hardDisks[num-1].pop_front();
            }
        }
        
        if(hardDisks[num-1].empty()) 
            checkIODevices = false;
            
    } catch (char const* error_message) {
        cout << "*Error; " << error_message << endl;
    }
    
}

//command - P #
void Memory::commandFinishWorkPrint(int num){
    
    PCB* temp;

    try {

        if(printers[num-1].empty()) 
            throw "Printer is idle";

        if(!printers[num-1].empty()){
            temp = findPidInMem(printers[num-1].front());
            if(temp == NULL)
                throw "Didn't find the pid in memory";
            else{
                addProcessToReadyQueue(temp -> priority, printers[num-1].front());
                printers[num-1].pop_front();
            }
        }
        
        if(printers[num-1].empty())
            checkIODevices = false;

    } catch (char const* error_message) {
        cout << "*Error; " << error_message << endl;
    }
    
}

//command - S m
void Memory::commandShowMemory(){
    
    try {

        if (head == NULL) 
            throw "Segmentation fault; Create a process!";

        PCB* p;
        p = head -> next;
        
        while(p != tail){
            cout << "\tP" << p -> pid << ": " << p -> begin << " - " << p -> end << endl;
            p = p -> next;
        }

    } catch(char const* error_message) {
        cout << error_message << endl;
    }
    
}