#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"
#include "shellmemory.h"
#include "interpreter.h"
#include "cpu.h"
#include "ram.h"



void initializeCPU()
{

	cpu = (struct CPU * ) malloc (sizeof(struct CPU));
	cpu->IP = -1;
	cpu->quanta = 2;

}

void runCPU(int end)
{
	if(cpu->IP > end)
	{
		cpu->IP = -1;
		return;
	}

	int i = 0;
	while(i < cpu->quanta)
	{
		if(cpu->IP + i > end) break;
		cpu->IR[i] = strdup(ram[cpu->IP + i]);
		i++;
	}

	int j = 0; 
	while(j < cpu->quanta)
	{
		if(cpu->IP > end)
		{
			cpu->IP = -1;
			break;
		}

		char *command;
		command = cpu->IR[j];
		interpreter(command);
		cpu->IP++;
		j++;
	}

}

