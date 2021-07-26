//
//  IO.h
//

#pragma once

#include <vector>
#include "CPU.h"

class IO : public CPU
{
    
public:
    bool checkIODevices = false;
    
    // the input/output devices
    int num_of_hard_disks = 0;   
    int num_of_printers = 0;
    
    // array of linked lists
    std::vector<std::list<int>> hardDisks;
    std::vector<std::list<int>> printers;
    
    // requesting when occupied
    void commandRequestHardDisk(int num);   //command - d
    void commandRequestPrinter(int num);    //command - p
    void commandShowIO();                   //command - S i
    
};