/**
 *  process.h
 *
 *  Full Name:
 *  Course section:
 *  Representation of a process in the system.
 *  
 */


#ifndef PROCESS_H
#define PROCESS_H

// representation of a a process
typedef struct process {
    int  pid;
    int  cpu_time;
    int  io_time;  
    int  arrival_time;
    int  state;
	int  CPU_remain_time;
	int  IO_remain_time;
	int  Turnaround_time;
} Process;

#endif
