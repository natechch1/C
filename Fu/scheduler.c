/**
 *  scheduler.c
 *
 *  Full Name:
 *  Course section:
 *  Description of the program:
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 

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

		for(int i=0; i<num_of_processes; i++){
			fscanf(fp, "%d %d %d %d",
					&queue[i].pid, 
					&queue[i].cpu_time, 
					&queue[i].io_time, 
					&queue[i].arrival_time);
			queue[i].state = 0;
			queue[i].CPU_brust = -1;
		}
		/*
		for(int i =0; i<num_of_processes; i++) {
			printf("A: %d B: %d  C: %d D: %d \n",
					queue[i].pid, 
					queue[i].cpu_time, 
					queue[i].io_time, 
					queue[i].arrival_time);    
		}*/
		

		int CPU_pid = -1;
		int CPU_brust = 0;
		float CPU_wait = 0;
		struct node *IO; //IO brust
		struct node *ready; // ready queue
		
		for(int t =0; t < INT_MAX; t++)	{
			
			//all finished
			int flag = 1;
			for(int i =0; i<num_of_processes; i++) {
				if(queue[i].state != 4)
				{
					flag = 0;
				}			
			}
			if(flag == 1) {
				printf("\nFinishing time:%d\n", t-1);
				printf("CPU utilization: %.2f\n", (t-CPU_wait)/t);
				for(int i =0; i<num_of_processes; i++) {
					printf("Turnaround process %d: %d\n", queue[i].pid, queue[i].turnaroundTime - queue[i].arrival_time );
				}
				break;
			}
			
			// check new arrival
			for(int i =0; i<num_of_processes; i++) {
				if(t == queue[i].arrival_time)
				{
					//add to the ready queue
					queue[i].state = 1;
					insert(&ready, &queue[i]);
				}
			}
			
			//cpu
			if(CPU_pid == -1) {//CPU free
				//pick by scheduler
				if(atoi(argv[2]) == 0) {
				//FCFS
				struct node *temp;
				temp = ready;

				if (temp != NULL) {

					while(temp->next != NULL){
						temp = temp->next;					
					}
					for(int i =0; i<num_of_processes; i++) {
						if(temp->process == &(queue[i]))
						{
							CPU_pid = i;
						}
					}

					if(temp->process->state == 1) {
						temp->process->CPU_brust = temp->process->cpu_time/2;//
						CPU_brust = temp->process->CPU_brust;
						//printf("%d %d\n", temp->process->CPU_brust, CPU_brust);
					}
					else{
						temp->process->CPU_brust = temp->process->cpu_time - (temp->process->cpu_time/2);
						CPU_brust = temp->process->CPU_brust;
						//printf("%d %d\n", temp->process->CPU_brust, CPU_brust);
					}
					delete(&ready, temp->process);
					
				}
				}
				
				if(atoi(argv[2]) == 1) {
				//RR
				struct node *temp;
				temp = ready;

				if (temp != NULL) {

					while(temp->next != NULL){
						temp = temp->next;					
					}
					for(int i =0; i<num_of_processes; i++) {
						if(temp->process == &(queue[i]))
						{
							CPU_pid = i;
						}
					}
					if(temp->process->CPU_brust == -1) {
						if(temp->process->state == 1) {
							temp->process->CPU_brust = temp->process->cpu_time/2;
							CPU_brust = 2;
							//printf("%d %d\n", temp->process->CPU_brust, CPU_brust);
						}
						else{
							temp->process->CPU_brust = temp->process->cpu_time - (temp->process->cpu_time/2);
							CPU_brust = 2;
							//printf("%d %d\n", temp->process->CPU_brust, CPU_brust);
						}
					}
					delete(&ready, temp->process);
					
				}
				}
				
				if(atoi(argv[2]) == 2) {
				//SJF
				struct node *temp;
				temp = ready;
				struct node *s;
				s = temp;

				if (temp != NULL) {
					int st;
					if(s->process->state == 1){
						st = s->process->cpu_time + s->process->io_time;
					}
					else	{
						st = s->process->cpu_time + s->process->io_time - (s->process->cpu_time/2);
					}
					while(temp->next != NULL){
						temp = temp->next;
						int tt;
						if(temp->process->state == 1){
							tt = temp->process->cpu_time + temp->process->io_time;
						}
						else	{
							tt = temp->process->cpu_time + temp->process->io_time - (temp->process->cpu_time/2);
						}
						if(tt<=st)	{
							s = temp;
						}
							
					}
					for(int i =0; i<num_of_processes; i++) {
						if(s->process == &(queue[i]))
						{
							CPU_pid = i;
						}
					}
					if(s->process->state == 1) {
						s->process->CPU_brust = s->process->cpu_time/2;
						CPU_brust = s->process->CPU_brust;
						//printf("%d %d\n", s->process->CPU_brust, CPU_brust);
					}
					else{
						s->process->CPU_brust = s->process->cpu_time - (s->process->cpu_time/2);
						CPU_brust = s->process->CPU_brust;
						//printf("%d %d\n", s->process->CPU_brust, CPU_brust);
					}
					
					delete(&ready, s->process);
					
				}
				}
			}

			//print
			printf("%d", t);
			for(int i =0; i<num_of_processes; i++) {
				/*
				if(queue[i].state == 0)
				{
					printf(" %d:not arrived", i);
				}*/
				if(queue[i].state == 1)
				{
					if(CPU_pid == i){
						printf(" %d:running", i);
					}
					else {
						printf(" %d:ready", i);
					}
				}
				if(queue[i].state == 2)
				{
					printf(" %d:blocked", i);
				}
				if(queue[i].state == 3)
				{
					if(CPU_pid == i){
						printf(" %d:running", i);
					}
					else {
						printf(" %d:ready", i);
					}
				}
				/*
				if(queue[i].state == 4)
				{
					printf(" %d:turnaround", i);
				}*/
				
			}
			printf("\n");
			
			//IO
			struct node *temp;
			temp = IO;

			while (temp != NULL) {
				temp->process->IO_brust--;
				if(temp->process->IO_brust == 0){
					temp->process->state++;
					insert(&ready, temp->process);
					delete(&IO, temp->process);
					
				}
				temp = temp->next;
			}
			
			
			//runing
			if(CPU_pid != -1) {
				queue[CPU_pid].CPU_brust--;
				CPU_brust--;
				if(queue[CPU_pid].CPU_brust == 0) {
					queue[CPU_pid].CPU_brust = -1;
					queue[CPU_pid].state++;
					if(queue[CPU_pid].state == 2) {
						insert(&IO, &queue[CPU_pid]);
						queue[CPU_pid].IO_brust = queue[CPU_pid].io_time;
					}
					if(queue[CPU_pid].state == 4) {
						queue[CPU_pid].turnaroundTime = t+1;
					}						
					CPU_pid = -1;
				}
				else {
					//RR
					if(CPU_brust == 0) {
						insert(&ready, &queue[CPU_pid]);
						CPU_pid = -1;
					}
				}
				
			}
			else {
				CPU_wait +=1.0;
			}	
		}
		
		
		


		free(queue); 
	}

	fclose(fp);


	return 0;
}
