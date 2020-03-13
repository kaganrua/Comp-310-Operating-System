#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "shell.h"
#include "interpreter.h"
#include "shellmemory.h"


#define MEM_LENGTH 100

typedef struct SHELLMEMORY {
	char *var;
	char *value;
	}shell_memory;

 	shell_memory mem[MEM_LENGTH];
 
void initializeShellMemory()
{
	for(int i=0; i < MEM_LENGTH; i++)
	{
		mem[i].var = NULL;
		mem[i].value = NULL;
	}
}

 int set_shell_memory(const char *var, const char *value)
 {
 	for (size_t i = 0; i < MEM_LENGTH; ++i)
 	{
 		if(mem[i].var == NULL)
 			continue;
 		if(strcmp(mem[i].var, var) == 0)
 		{
 			free(mem[i].value);
 			mem[i].value = strdup(value);
 			return 0;
 		}
 	}

 	size_t cell = MEM_LENGTH;
 	for(int j=0; j<MEM_LENGTH; ++j)
 	{
 		if(mem[j].var == NULL && mem[j].value == NULL)
 		{
 			cell = j;
 			break;
 		}
 	}
 	if(cell == MEM_LENGTH)
 	{
 		return -1;
 		printf("No available cell in shellmemory\n");
 	}
 	else
 	{
 		mem[cell].var = strdup(var);
 		mem[cell].value = strdup(value);
 		return 0;
 	}
 }

 const char *getFromShellMemory(const char *var)
 {
 	
 	for (size_t i = 0; i < MEM_LENGTH; ++i)
    {
        if (mem[i].var == NULL)
            continue;
        if (strcmp(mem[i].var, var) == 0)
            return mem[i].value;
    }
    return NULL;
}
 

 
	