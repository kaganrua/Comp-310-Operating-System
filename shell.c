#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "interpreter.h"
#include "shell.h"
#include "shellmemory.h"



#define MAX_INPUT_SIZE 1000

int checkInputSize(char *input, int limit)
{
	if(strlen(input) < limit)
	{
		return 0;
	}
	else
	{
		
		return 1;
	}
}

char **parse(char *str)
{
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }
    char **ret_arr = (char **)calloc((num_tokens+1), sizeof(char *) * (num_tokens + 1));

    if (ret_arr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    flag = 0;
    int ignore_flag = 0;
    char *modified_str = (char *)str;
    size_t counter = 0;
    const size_t length_str = strlen(str);
    for (size_t i = 0; i < length_str; i++)
    {
        if (modified_str[i] == '\n' || modified_str[i] == '\r')
            modified_str[i] = ' ';
        if (modified_str[i] == '"')
        {
            ignore_flag = ignore_flag ^ 0x1;
        }
        if (flag == 0 && modified_str[i] != ' ')
        {
            ret_arr[counter] = &(modified_str[i]);
            counter = counter + 1;
            flag = 1;
        }
        if (modified_str[i] == '\\' && modified_str[i + 1] == ' ')
        {
            i++;
            continue;
        }
        if (flag == 1 && modified_str[i] == ' ' && ignore_flag == 0)
        {
            modified_str[i] = '\0';
            flag = 0;
            continue;
        }
    }
    ret_arr[counter] = NULL;

    for (size_t i = 0; i < counter; ++i)
    {
        if (ret_arr[i][0] == '\"' &&
            ret_arr[i][strlen(ret_arr[i] - 1)] == '\"')
        {
            ret_arr[i][strlen(ret_arr[i]) - 1] = '\0';
            ret_arr[i] = ret_arr[i] + 1;
        }
    }

    return ret_arr;
}


 /*	int w=0;
	int b;
	char *words[1000];
	char tmp[1000];
	
	
	//skip the white spaces.
	for(a=0; ui[a] == ' '; a++);


	while(ui[a] != '\0' || ui[a] != '\n' || a<1000)
	{
		
		for(b=0; ui[a] != '\0' && (ui[a] != ' ') && ui[a] != '\n' && a < 1000; a++,b++)
		{

				tmp[b] = ui[a];
		}

		
		
		tmp[b] = '\0';
		
		

		words[w] = strdup(tmp);
		
		if(ui[a] == '\0' || ui[a] == '\n') break;

		w++;
		a++; 
		
	}

	return interpreter(words);

*/
 

int shellUI()
{
	int errCode = 0;
	printf("Kernel 1.0 loaded!\n");
	printf("Welcome to the Kagan's Shell\n");
	printf("Shell version 2.0 created in February 2020. Please enter your command Sir\n");
	char prompt[100] = {'$' , '\0'};
	char ui[MAX_INPUT_SIZE];

	while(1)
	{
		printf("%s" , prompt);
		fgets(ui, 999, stdin);

		if(checkInputSize(ui, MAX_INPUT_SIZE) == 1)
		{
			printf("Input size is too large\n");
			errCode = 1;
			continue;
		}
		errCode = interpreter(ui);


	}

	return errCode;






}
