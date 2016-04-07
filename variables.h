#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#define VARIABLES_COUNTER 100
#define MAXIMUM_NAME 100

void ClearVarTable(void);
void ClearVarTableGlobal(void);
int GettingVariables(char *Buffer, double *resource);
int SettingVariables(char *Buffer, double value);
int SettingVariablesGlobal(char *Buffer, double value);

typedef struct tag_VAR
{
	char name[MAXIMUM_NAME];
	double value;
} VARIABLES;

#endif