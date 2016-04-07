#include <string.h>
#include "variables.h"

VARIABLES VarTable[VARIABLES_COUNTER], VarTableGlobal[VARIABLES_COUNTER];
int VariableCounter = 0, VariableCounterGlobal = 0;

int GettingVariables(char *Buffer, double *resource)
{
	int i = 0;

	for (i = 0; i < VariableCounter; i++)
		if (strncmp(Buffer, VarTable[i].name, strlen(VarTable[i].name)) == 0)
		{
			*resource = VarTable[i].value;
			return (int) strlen(VarTable[i].name);
		}
	for (i = 0; i < VariableCounterGlobal; i++)
		if (strncmp(Buffer, VarTableGlobal[i].name, strlen(VarTableGlobal[i].name)) == 0)
		{
			
			*resource = VarTableGlobal[i].value;
			return (int) strlen(VarTableGlobal[i].name);
		}
	return 0;
}

//set time variables
int SettingVariables(char *Buffer, double value)
{
	if (VariableCounter < VARIABLES_COUNTER)
	{
		
		strncpy_s(VarTable[VariableCounter].name, sizeof(char) *MAXIMUM_NAME, Buffer, sizeof(char) *MAXIMUM_NAME);
		VarTable[VariableCounter].value = value;
		VariableCounter++;
		return 1;
	}
	else
		return 0;

}

//set global variables
int SettingVariablesGlobal(char *Buffer, double value)
{
	if (VariableCounterGlobal < VARIABLES_COUNTER)
	{
		strncpy_s(VarTableGlobal[VariableCounterGlobal].name, sizeof(char) *MAXIMUM_NAME, Buffer, sizeof(char) *MAXIMUM_NAME);
		VarTableGlobal[VariableCounterGlobal].value = value;
		VariableCounterGlobal++;
		
		return 1;
	}
	else
		return 0;

}



//delete time variables
void ClearVarTable(void)
{
	VariableCounter = 0;
}
//delete global variables
void ClearVarTableGlobal(void)
{
	VariableCounterGlobal = 0;
}