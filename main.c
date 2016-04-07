//standart .h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
//local .h
#include "calculator.h"
#include "conio.h"

int main(int Argc, char *Argv [])
{
	FILE *file = stdin;
	char *buffer = NULL;
	char *bufferPtr;
	int  shetchik = 0;
	if (Argc == 2)
	{
		fopen_s(&file, Argv[1], "rt");
		if (file == NULL)
		{
			printf("\nERROR: NO FILE");
			return 1;
		}
	}
	if (Argc > 2)
	{
		printf("\nERROR: TOO MUCH ARG");
	}
	while ((shetchik = getstring(file, &buffer)) != 1)
	{
		SetError(No_error);
		if (shetchik == 2)
		{
			if (feof(file))
				printf("ERROR: %s", GetLastErrorDescription());
			else
				printf("ERROR: %s\n",GetLastErrorDescription());
			SetError(No_error);
		}
		else
		{
			bufferPtr = buffer;
			while (IS_SPACE(*bufferPtr))
				bufferPtr++;
			if (*bufferPtr == 0 || (bufferPtr[0] == '/' && bufferPtr[1] == '/'))
			{
				if (feof(file))
					printf("%s", buffer);
				else
					printf("%s\n", buffer);
			}
			else
			{
				double resource;
				resource = Calculator(bufferPtr);
				//delete all variables
				ClearVarTable();
				if (IsError())
				{
					if (feof(file))
						printf("%s == ERROR: %s", buffer, GetLastErrorDescription());
					else
						printf("%s == ERROR: %s\n", buffer, GetLastErrorDescription());
					SetError(No_error);

				}
				else
					if (feof(file))
						printf("%s == %g", buffer, resource);
					else
						printf("%s == %g\n", buffer, resource);
			}
			free(buffer);
		}
	}
	if (file != stdin)
		fclose(file);
	//delete all variables
	ClearVarTableGlobal();
	return 0;
}