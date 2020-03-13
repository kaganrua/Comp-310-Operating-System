#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"
#include "shellmemory.h"
#include "interpreter.h"
#include "ram.h"
#include "cpu.h"
#include "pcb.h"

struct PCB *head, *tail;

void initializeReady()
{
	head = tail = NULL;
}

void addToReadyQueue(struct PCB *pcb)

{
	pcb->next = NULL;
	if(tail == NULL)
	{
		head = pcb;
		tail = pcb;
		return;
	}
	tail->next = pcb;
	tail = tail->next;

}



int myInit(char *filename)
{
	FILE *p = fopen(filename, "r");
	if(p == NULL)
	{
		printf("File Not Found!\n");
		return -1;
	}
	int start;
	int end;
	load_to_ram(p, &start, &end);
	
	struct PCB* pcb = makePCB(start, end);
	addToReadyQueue(pcb);

	return 0;
}

void dequeue()
{
	if(head == NULL)
	{
		return;
	}

	struct PCB* tmp = head;
	head = head->next;

	if(head == NULL)
	{
		tail = NULL;
	}

}

void scheduler()
{
	while(head != NULL)
	{
		struct PCB* tmp = head;
		dequeue();
		cpu->IP = tmp->PC;

		runCPU(tmp->end);

		if(cpu->IP < 0)
		{
			removefromram(tmp->start, tmp->end);
			free(tmp);

		}
		else
		{
			tmp->PC = cpu->IP;
			addToReadyQueue(tmp); 
		}
	}
}


int main(int argc, char* argv[])
{
	initializeShellMemory();
	initializeReady();
	initialize_ram();
	initializeCPU();
	shellUI();
}