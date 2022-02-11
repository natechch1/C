/**
 *  scheduler.c
 *
 *  Full Name: Hongce Chen
 *  Course section: M
 *  Description of the program:
 *   说明四个state
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "scheduler.h"
#include "process.h"

#define SIZE    100

int main(int argc, char *argv[])
{
	FILE *fp;

	int num_of_processes;

	fp  = fopen(argv[1],"r");
	fscanf(fp, "%d", &num_of_processes);    
	if (num_of_processes > 0){
		Process *queue = malloc(num_of_processes * sizeof(Process));      

		for (int i=0; i<num_of_processes; i++){
			fscanf(fp, "%d %d %d %d",
					&queue[i].pid, 
					&queue[i].cpu_time, 
					&queue[i].io_time, 
					&queue[i].arrival_time); 
			//let the process state and the cpu remain time to be new value
			queue[i].state = 0;				
			queue[i].CPU_remain_time = -1;
		}                                                                               
		/*
		for(int i =0; i<num_of_processes; i++) {
			printf("A: %d B: %d  C: %d D: %d \n",
					queue[i].pid, 
					queue[i].cpu_time, 
					queue[i].io_time, 
					queue[i].arrival_time);    
		}*/

		int pid = -1;
		int CPU_remain_time = 0;
		float CPU_free_time = 0;
		struct node *IO;      // !!!还是不知道
		struct node *ready_queue;

		int t = 0;    //t here is total time
		int check_finished = 0;  //the value if the process finished


		while(check_finished == 1)
		{
			//if all process finished. it will end the while loop.
			check_finished = 1;
			for (int i = 0; i < num_of_processes; i++)
			{
				/*if one of process's state is not 4,
				 the whole thing is not finished.*/
				if (queue[i].state != 4) check_finished = 0;
				
				//变化处 （对应line 79）
				//check and get new arrival
				if (t == queue[i].arrival_time)
				{	
					//if it reach the arrival time, make the state be 1
					queue[i].state = 1; 
					//add it to the ready queue
					insert(&ready_queue, &queue[i]);
				}
				
			}

			//CPU part
			if (pid == -1)   // -1 it means the cpu is free now
			{
				//FCFS part
				if (atoi(argv[2]) == 0)  
				{
					struct node * current;
					current = ready_queue;

					if (current != NULL)
					{
						// get the last node 
						while (current->next != NULL)
						{
							current = current->next;
						}
						
						for (int i = 0; i < num_of_processes; i++)
						{	
							// check and get the process ID
							if(current->process == &(queue[i])) pid = i; 
						}

						if (current->process->state == 1)
						{
							// the CPU running time of State 1
							current->process->CPU_remain_time = current->process->cpu_time * 0.5;
							CPU_remain_time = current->process->CPU_remain_time;
						}else
						{
							// the CPU running time of State 3
							 current->process->CPU_remain_time = current->process->cpu_time - (current->process->cpu_time * 0.5);
							 CPU_remain_time = current->process->CPU_remain_time;
						}
						
						delete(&ready_queue, current->process);
						
						
					}
				}

				//RR part
				//SJF part
			}

		//print part
		printf("%d ", t);
		for (int i = 0; i < num_of_processes; i++)
		{
			// print State 1 process which has two part: ready and running 
			if (queue[i].state == 1)   
			{
				if (pid != i)
				{
					printf("%d:ready ", i);
				}else
				{
					printf("%d:running ", i);
				}	
			}

			//print State 2 process
			if (queue[i].state == 2)
			{
				printf("%d:blocked ", i);
			}

			//print State 3 process which has two part: ready and running
			if (queue[i].state == 3)
			{
				if (pid != i)
				{
					printf("%d:ready ", i);
				}else
				{
					printf("%d:running ", i);
				}
			}

		}
		printf("\n");


		//IO
		struct node *current;
		//IO = NULL;
		current = IO;

		while (current != NULL)
		{
			//let all process in the IO queue minus 1
			current->process->IO_remain_time = current->process->IO_remain_time - 1;
			// untill the IO remain time minus to 0			
			if(current->process->IO_remain_time == 0)
			{
				//let the State 2 become State 3
				current->process->state = current->process->state + 1;
				//add it to the ready queue
				insert(&ready_queue, current->process);
				//delete it from the IO queue
				delete(&IO, current->process);
			}
			// check next node
			current = current->next;
		}
		


		//running
			

			
			 

			


		t++;		
		}
		
		//print the finished time , CPU utiliazation and Turnaround process time.		
		printf("\nFinishing time:%d\n", t-1);
		printf("CPU utiliazation: %.2f\n", (t-CPU_free_time)/t);
		for (int i = 0; i < num_of_processes; i++)
		{
			int Turnaround_final_time = queue[i].Turnaround_time - queue[i].arrival_time;
			printf("Turnaround process %d: %d\n", queue[i].pid, Turnaround_final_time);
		}
			
		
		

		free(queue); 
	}

	fclose(fp);


	return 0;
}
