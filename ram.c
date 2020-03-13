#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"
#include "shellmemory.h"
#include "interpreter.h"
#include "pcb.h"
#include "ram.h"
#include "cpu.h"
#include "kernel.h"





void initialize_ram()
{
	for(int i=0; i<RAM_LENGTH; i++)
	{	
	ram[i] = NULL;
	}
}

void load_to_ram(FILE *p, int *start, int *end)
{
	int ram_pointer = 0;
	
	int e = 0;

	if(ram_pointer == RAM_LENGTH)
	{
		printf("There's no space in ram.\n");
		return;
	}

	while(ram[ram_pointer] != NULL)
	{
		ram_pointer++;
		if(ram_pointer == RAM_LENGTH)
		{
		printf("There's no space in ram.\n");
		return;
		}
	}

		*start = ram_pointer;
	
		
		char line[100];


		while(fgets(line,99,p) != NULL)
		{
			
			ram[ram_pointer] = strdup(line);
			
			
			e = ram_pointer;
			ram_pointer++;

			if(ram_pointer >= RAM_LENGTH)
			{
				printf("There's not enough space in RAM!\n");
			}
			

		}
		
		*end = e;
		


		fclose(p);
}

void removefromram(int start, int end)
{
	if(start < 0 || end >= RAM_LENGTH)
	{
		printf("Invalid Ram cell!\n");
		return;
	}

	while(start <= end)
	{
		ram[start] = NULL;
		start++;
	}

}

void clear_ram()
{
	for(int i=0; i<RAM_LENGTH; i++)
	{
		ram[i] = NULL;
		printf("Ram has been cleared. Please retry with another script or modify your script.\n");
	}
	
}
