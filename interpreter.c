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
#include "kernel.h"



// -1 = quit.
// 1 = there's a error. Command does not run
// 0 = Command have run successfully
int in_file_flag = 0;

int run(char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Script not found.\n");
        return 1;
    }
    int enter_flag_status = in_file_flag;
    in_file_flag = 1;
    while (!feof(file))
    {
        char *line = NULL;
        size_t linecap = 0;
        getline(&line, &linecap, file);

        int status = interpreter(line);
        free(line);
        if (status != 0)
        {
            break;
            return status;
        }
    }
    fclose(file);
    in_file_flag = enter_flag_status;
    return 0;
}


 
int help()
{	
	
	printf("Commands are case sensitive\n\nhelp\tDisplays all the commands\nquit\tTerminates the shell\nset VAR STRING\tAssigns a value to shellmemory\nprint VAR\tprints the value assigned to variable\nrun SCRIPT.TXT\tExecutes the file SCRIPT.TXT\n");
	return 0;
	
}
int quit()
{
	printf("Have a nice day good Sir\n");
	exit(99);
	return -1;
}


int exec(char* programs[])
{
	int errCode = 0;
	if(programs[2] != NULL)
	{
		if(strcmp(programs[1], programs[2]) == 0)
		{
			printf("Script cannot have same name");
			return -1;
		}
		if(programs[3] != NULL)
		{
				if(strcmp(programs[1],programs[2]) == 0 || strcmp(programs[2],programs[3]) == 0)
				{
					printf("Script cannot have same name");
					return -1;
				}
				else
				{
					errCode = myInit(programs[1]);
					errCode = myInit(programs[2]);
					errCode = myInit(programs[3]);
				}
		}

		else
		{
			errCode = myInit(programs[1]);
			errCode = myInit(programs[2]);
		}

	}
	else
	{
		errCode = myInit(programs[1]);
	}

    scheduler();

	return errCode;




}		


/*


	int errCode=0;
	int program_counter = 1;
	

	if(*programs + 1 == NULL)
	{
		printf("Input cannot be null. Please enter at least 1 file\n");
		return -1;
	}

	if(*programs + 2 != NULL)
	{
		if(strcmp(programs[1], programs[2]) == 0)
		{
			printf("Scripts cannot have the same name.\n");
			return -1;
		}
	}

	if(* programs + 3 != NULL)
	{
		if(strcmp(programs[1], programs[3]) == 0 || strcmp(programs[2], programs[3]) == 0)
		{
			printf("Scripts cannot have the same name.\n");
			return -1;
		}
	}
	if(programs[4] != NULL)
	{
		printf("Exec cannot run more than 3 programs\n");
		return -1;
	}

	int i=1;
	
	while(programs != NULL)
	{

		errCode = myInit(programs[i]);
		if(errCode != 0)
		{
			return errCode;
		}
		programs++;
		i++;

	}

	scheduler();

	clear_ram();
	return errCode;
	
}
	
*/


int set(const char *var, const char *value)
{
    int errCode = set_shell_memory(var,value);
    if(errCode != 0)
    {
        printf("Set command run unsuccesfully");
    }
    return errCode;
}

int print(const char *var)
{
    const char *value = getFromShellMemory(var);
    if(value == NULL)
    {
        printf("Variable haven't been assigned yet!\n");
        return 1;
    }
    printf("%s = %s \n" , var , value );
    return 0;

}



int interpreter(char *words)
{
	
    char **tokens = parse(words);

    if (tokens[0] == NULL)
        return 0; // empty command

    if (strcmp(tokens[0], "help") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("help: Malformed command\n");
            free(tokens);
            return 1;
        }
        free(tokens);
        return help();
    }

    if (strcmp(tokens[0], "quit") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("quit: Malformed command\n");
            free(tokens);
            return 1;
        }
        if (in_file_flag == 0) {
            free(words);
        }
        free(tokens);
        return quit();
    }

    if (strcmp(tokens[0], "set") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] != NULL && tokens[3] == NULL))
        {
            printf("set: Malformed command\n");
            free(tokens);
            return 1;
        }
        int status = set(tokens[1], tokens[2]);
        free(tokens);
        return status;
    }

    if (strcmp(tokens[0], "print") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("print: Malformed command\n");
            free(tokens);
            return 1;
        }
        int status = print(tokens[1]);
        free(tokens);
        return status;
    }

    if (strcmp(tokens[0], "run") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("run: Malformed command\n");
            free(tokens);
        }
        int result = run(tokens[1]);
        free(tokens);
        return result;
    }

    if (strcmp(tokens[0], "exec") == 0)
    {
        if (!(tokens[1] != NULL && tokens[4] == NULL))
        {
            printf("exec: Malformed command\n");
            free(tokens);
        }

        int result = exec(tokens);
        free(tokens);
        return result;
    }

    printf("Unrecognized command \"%s\"\n", tokens[0]);
    free(tokens);
    return 1;


}


