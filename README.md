# Lifecycle of a Process

The program simulates aspects of operating system. It simulates the lifecycle of a process with priority scheduling and memory management with "first-fit" approach.


#### Scheduling: 

There are 5 priority ready-queues, priority levels numbered from 0 to 4 (0 is the lowest priority, and 4 is the highest). Within each level of the ready-queue the FCFS algorithm is used. A process from some level of the ready-queue can be scheduled only if all higher levels are empty. However, the scheduling is preemptive: When a higher priority process becomes available for execution the lower priority process is preemptied and sent to the end of its level of the ready queue.

#### Memory:

Memory allocation managed with "first-fit" appraches: partition is allocated which is first sufficient from the top of memeory.


## Usage
The program starts asking the user as followed:
```
Please enter the number of RAM memory you would like to use (in Bytes):    //RAM memory size
Please enter the number of Hard Disks you would like to use:               //Number of Hard Disks
Please enter the number of Printers you would like to use:                 //Number of Printers
```
After these questions, the simulation starts. The program constantly listens for the user inputs. The user inputs signal some system events. The program simulates the corresponding system behavior.
The user is allowed to type any commands as listed below to simulate the system.


## Commands
Type "c" to see all the commands while running.

The commands are as listed below: 
```
A <priority> <size> - Create a new process 
t - Terminate the process in CPU
d <disk number> - The process that currently uses the CPU requests the hard disk #number. 
p <printer number> - The process that currently uses the CPU requests the printer #number.
D <disk number> - The hard disk #number has finished the work for one process.
P <printer number> - The printer #number has finished the work for one process.
S r - Shows what process is currently using the CPU and what processes are waiting to use the CPU on each level of the ready-queue. 
S i - Shows what processes are currently using the I/O devices and what processes are waiting to use them.
S m - Shows the state of memory.
```

#### The commands details:
```
$ A <priority> <size>
```
"A" means that a new process has been created. This command also takes the process's priority and size bytes of RAM memory. 

When the new process is created, this command creates its PCB(Process Control Block) to keep track of the process in memory (The new process cannot be created when there is no enough space for it in memory.) , it also sends the new process to to the ready-queue or allow it to use the CPU right away. When choosing PID(process ID) for a new process, the PID starts from 1 and go up (The PIDs of the terminated processes cannot be reused).

```
$ t
```
The process that currently uses the CPU terminates. It leaves the system immedietly. 

This command releases the memory used by the process (If the process was positioned in memory next to a hole, its memory is merged with the hole to avoid creating adjacent holes).

```
$ d <disk number>
```
The process that currently used the CPU requests the hard disk #number.

This command moves the process to the hard disk #number or its ready-queue if the hard disk in use. The process at the first place of the CPU's ready-queue is pushed to the CPU if any. 

```
$ p <printer number>
```
The process that currently uses the CPU requests the printer #number.

This command moves the process to the printer #number or its ready-queue if the printer is in use. The process in the first place of the CPU's ready-queue is pushed to the CPU if any.

```
$ D <disk number>
```
The hard disk #number has finished the work for one process.

This command moves the process in the hard disk to the CPU. The process that was in the CPU is pushed back to its ready-queue.

```
$ P <printer number>
```
The printer #number has finished the work for one process.

This command moves the process in the printer to the CPU. The process that was in the CPU is pushed back to its ready-queue.

## Run the program
To compile
```
$ make
```
To run
```
$ ./os
```
