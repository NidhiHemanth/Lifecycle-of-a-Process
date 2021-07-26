//
//  main.cpp
//

#include <iostream>
#include <string>
#include <sstream>  // used for read/write to a string, treating it as a file
#include <stddef.h> // size_t
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

#include "CPU.h"
#include "Memory.h"
#include "IO.h"

using namespace std;

// Global memory object
Memory mem;

bool validInput(double input);
void userInputCommands(string userInput);

int main() {
    
    string userInput;
    bool userWantToContinue = true;
    
    //How much RAM memory? (receive # in bytes up to 4000000000)
    cout << "Please enter the number of RAM memory you would like to use (in Bytes): ";
    cin >> mem.size_of_memory;
    while(!validInput(mem.size_of_memory)){
        cin >> mem.size_of_memory;
    }
    
    //How many hard disks? (Enumeration starts with 0)
    cout << "Please enter the number of Hard Disks you would like to use: ";
    cin >> mem.num_of_hard_disks;
    while(!validInput(mem.num_of_hard_disks)){
        cin >> mem.num_of_hard_disks;
    }
    mem.hardDisks.resize(mem.num_of_hard_disks);
    
    //How many printers? (Enumeration starts with 0)
    cout << "Please enter the number of Printers you would like to use: ";
    cin >> mem.num_of_printers;
    while(!validInput(mem.num_of_printers)){
        cin >> mem.num_of_printers;
    }
    mem.printers.resize(mem.num_of_printers);
    
    cout << "\t/--------------------------------" << endl;
    cout << "\t  You have created a system with" << endl;
    cout << "\t  RAM memory: " << mem.size_of_memory << " bytes" << endl;
    cout << "\t  Hard Disks: " << mem.num_of_hard_disks << endl;
    cout << "\t  Printers: " << mem.num_of_printers << endl;
    cout << "\t---------------------------------/" << endl;

    // after a getline is used, the "\n" by the user to submit the input
    // could mess with the next input
    // hence clear the buffer up to the string that you want
    // The 10000 is put there to skip over a specific amount of chars before the specified break point, in this case, the \n newline character.
    cin.ignore(10000, '\n');
    
    //simulation begins
    while(userWantToContinue){
        cout << "Please enter your command ('c' for command details, 'e' to exit): ";
        getline(cin,userInput);
        
        if(userInput == "e"){
            userWantToContinue = false;
        }
        else{
            userInputCommands(userInput);
        }
    }
    return 0;
}

void userInputCommands(string userInput){
    
    try {

        if(userInput.at(0) == 'A'){
            
            // userInput = 'A <priority> <size>'   eg: A 2 10

            char a;
            int priority = -1;
            double size = -1;
            
            stringstream ss;
            ss << userInput;
            ss >> a >> priority >> size;
            // a = 'A'
            // priority = 2  (turns string type into int)
            // size = 10     (turns string type into int)
            
            if(priority == -1 or size == -1)  //when priority or size is empty
                throw "Input has to have both priority and size (non-negative).";
            else if(priority < 0 or 4 < priority)
                throw "The priority has to be the number from 0 to 4.";
            else if(size < -1 or size > mem.size_of_memory)
                throw "The size of the memory has to be non-negative and less than the size of the memory you created.";
            else
                mem.commandAdd(priority, size);  //command - A                      
            
        }

        else if(userInput == "t")
        {                                       //command - t
            if(mem.head == NULL)
                throw "No process to terminate!";
            mem.commandTerminate();
        }

        else if(userInput.at(0) == 'd'){
            
            // userInput = 'd <disk-number>'   eg: d 1

            char d;
            int num = -1;
            
            stringstream ss;
            ss << userInput;
            ss >> d >> num;
            // d = 'd', num = 1
            
            if(num == -1)
                throw "Please mention Hard Disk Number.";
            else if(num < 1 or num > mem.num_of_hard_disks)
                throw "The number must be bigger than 1 and smaller than the number of hard disks you created.";
            
            mem.commandRequestHardDisk(num);   //command - d
            
        }

        else if(userInput.at(0) == 'p')
        {
            
            // userInput = 'p <printer-number>'   eg: p 1

            char p;
            int num = -1;
            
            stringstream ss;
            ss << userInput;
            ss >> p >> num;
            // p = 'p', num = 1
            
            if(num == -1)
                throw "Please mention Printer Number.";
            else if(num < 1 or num > mem.num_of_printers)
                throw "The number must be bigger than 1 and smaller than the number of printers you created.";
            
            mem.commandRequestPrinter(num);     //command - p
            
        }
        
        else if(userInput.at(0) == 'D'){

            // userInput = 'D <disk-number>'   eg: D 1

            char e;
            int num = -1;
            
            stringstream ss;
            ss << userInput;
            ss >> e >> num;
            
            if(num == -1)
                throw "Please mention Hard Disk Number.";
            else if(num > mem.num_of_hard_disks)
                throw "Hard Disk doesn't exist";
            
            mem.commandFinishWorkHardDisk(num);     //command - D
            
        }
        
        else if(userInput.at(0) == 'P'){

            // userInput = 'P <printer-number>'   eg: P 1

            char q;
            int num = -1;
            
            stringstream ss;
            ss << userInput;
            ss >> q >> num;
            
            if(num == -1)
                throw "Please mention Printer Number.";
            else if(num > mem.num_of_printers)
                throw "Printer doesn't exist";
            
            mem.commandFinishWorkPrint(num);    //command - P
            
        }
        
        else if(userInput.at(0) == 'S'){

            // S r - process using the CPU & waiting in the ready-queue.
            // S i - processes using the I/O & waiting to use them.
            // S m - Shows the state of memory.

            char s;
            char t;
            
            stringstream ss;
            ss << userInput;
            ss >> s >> t;
            
            if(t == 'r'){
                mem.commandShowReadyQueueAndCPU();    //command - S r
            }
            else if(t == 'i'){
                mem.commandShowIO();    //command - S i
            }
            else if (t == 'm'){
                mem.commandShowMemory();    //command - S m
            }
            else
                throw " ";
        }
        
        else if(userInput == "c"){
            
            // Display the commands from the file "c.txt"

            string line;
            ifstream inputFile("c.txt");

            if(inputFile.is_open()){
                while(getline(inputFile, line)){
                    cout << line << endl;
                }
                inputFile.close();
            }
            else
                throw 101;
                // Unable to open the text file
            
        }
        
        else
            throw " ";

    } catch (int k) {
    
        if(k == 101) 
            cout << "\tUnable to open the text file" << endl;

    } catch (char const* error_message) {
    
        cout << "\t*Invalid command; " << error_message << endl;
    
    } 
}


//check if the input is valid
bool validInput(double input){
    
    if(input < 0 or 4000000000 < input){
        
        cout << "\t*Invalid input; It has to be the number between 0 to 4 billions." << endl;
        cout << "Please enter the number again: ";
        return false;
    }
    else if(!input){   //check if the input is number

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t*Invalid input; It has to be a number." << endl;
        cout << "Please enter the number again: ";
        return false;
    }
    else{
        return true;
    }

}