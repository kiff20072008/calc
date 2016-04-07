//standart .h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
//local .h
#include "conio.h"
#include "error.h"


//function get file and return string 
int getstring(FILE *file, char **buffer)
{
	
	int number_of_blocks = 1;
	int ch;
	int shetchik = 0;
	if (feof(file))
		return 1;
	//malloc memory
	*buffer = (char*) malloc(SIZE_ALLOC_MEMORY * sizeof(char) *number_of_blocks);
	if ( *buffer== NULL)
	{
		if ((ch = fgetc(file)) == EOF)
			return 1;
		if (ch == '\n')
		{
			SetError(no_memory);
			return 2;
		}
		//if NULL get string to the end and return 1 or 2 
		while (((ch = fgetc(file)) != EOF) && (ch != '\n'));
		if (ch == EOF)
			return 1;
		SetError(no_memory);
		return 2;
	}
	//get char while not get \n or EOF
	while ((ch = fgetc(file)) != '\n')
	{
		if (ch == EOF)
			break;
		if (ch > 255 || ch < 0)
		{
			SetError(wrong_simbol);
			return 0;
		}
		
		if (shetchik >= (SIZE_ALLOC_MEMORY*number_of_blocks - 1))
		{
			char *temp;
			++number_of_blocks;
			temp = (char*) realloc(*buffer, SIZE_ALLOC_MEMORY*number_of_blocks*sizeof(char));
			if (temp  == NULL)
			{
				while (((ch = fgetc(file)) != EOF) && (ch != '\n'));
				if (ch == EOF)
					return 1;
				SetError(no_memory);
				return 2;
			}
			*buffer = temp;
		}
		
		assert(*buffer != NULL);
			(*buffer)[shetchik] = (char) ch;
		++shetchik;
	}
	if (shetchik <= (SIZE_ALLOC_MEMORY * number_of_blocks - 1))
		(*buffer)[shetchik] = '\0';
	return 0;
}

