//standart .h
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>

//local .h
#include "calculator.h"
#include "error.h"
#include "functions.h"


CONTEXT Context;

//fucntion get string and return result
double Calculator(char const *const BufferPtr)
{
	
	double resource;//result
	char *ravno, *zap, *dvoet;//ukasateli for ; and = and :

	assert(BufferPtr != NULL);
	Context.Offset = 0;
	Context.Buffer = (char *) malloc(strlen(BufferPtr) +1 );

	//if no memory return to main or to function 
	if (Context.Buffer == NULL)
	{
		SetError(no_memory);
		return 0;
	}

	memcpy(Context.Buffer, BufferPtr, strlen(BufferPtr) +1 );

	//cut all probels
	PROBELI();

	if (IsError())
	{
		free(Context.Buffer);
		return 0;
	}

	//searching variables and counting its value
	while ((zap = strchr(Context.Buffer + Context.Offset + 1, ';')) != NULL)
	{
		if ((ravno = strchr(Context.Buffer + Context.Offset, '=')) != NULL)
		{
			CONTEXT Saved;

			dvoet = ravno - 1;
			Saved.Buffer = Context.Buffer;
			Saved.Offset = Context.Offset;

			//set to 0 to calculate string from "=" to ";"
			*zap = 0;
			*ravno = 0;

			Context.Offset = ravno - Context.Buffer + 1;

			resource = Calculator(Context.Buffer + Context.Offset);

			if (IsError() == no_memory)
				return 0;
			//setting variables
			if (*dvoet == (char)':')
			{
				*dvoet = 0;
				if (!SettingVariablesGlobal(Saved.Buffer + Saved.Offset, resource))
					SetError(variable_name_too_long);
				*dvoet = ':';
			}
			else
				if (!SettingVariables(Saved.Buffer + Saved.Offset, resource))
					SetError(variable_name_too_long);
			Context.Buffer = Saved.Buffer;
				
			*zap = ';';
			*ravno = '=';

			Context.Offset = zap - Saved.Buffer + 1;
		}
		else
			break;;
		
	}
	
	//go to first function 
	resource = PLUS();

	if (IsError())
	{
		free(Context.Buffer);
		return 0;
	}

	if (Context.Buffer[Context.Offset] != 0)
		SetError(Syntax_error);

	free(Context.Buffer);

	return resource;
}


static double PLUS(void)
{
	//result
	double resource;
	//go to second function  
	resource = DELENIE();

	if (IsError())
		return 0;
	//search for "+" and "-" and calculating
	while (Context.Buffer[Context.Offset] == '+' || Context.Buffer[Context.Offset] == '-')
	{
		switch (Context.Buffer[Context.Offset])
		{

		case '-':
			Context.Offset++;
			resource = resource - DELENIE();
			if (IsError() )
				return 0;
			break;
		case '+':
			Context.Offset++;
			resource = resource + DELENIE();
			if (IsError())
				return 0;
			break;
		}

	}

	return resource;
}


static double DELENIE(void)
{
	//result
	double resource, tmpresource;

	//go to third function 
	resource = MINUS();

	if (IsError())
		return 0;
	//searching for "*" and"/" and calculate
	while (Context.Buffer[Context.Offset] == '*' || Context.Buffer[Context.Offset] == '/')
	{

		switch (Context.Buffer[Context.Offset])
		{

		case '/':

			Context.Offset++;

			tmpresource = MINUS();

			if (IsError())
				return 0;

			if (fabs(tmpresource) > THRESHOLD)
				resource = resource / tmpresource;
			else

				SetError(Divide_by_zero);
			break;
		case '*':
			Context.Offset++;

			resource = resource * MINUS();

			if (IsError())
				return 0;
			break;


		}

	}
	return resource;
}

static double MINUS(void)
{
	double resource = 1.0;

	//if found "-" or "+" without number before it calculaet unar minus 
	if (Context.Buffer[Context.Offset] == '-' || Context.Buffer[Context.Offset] == '+')
	{
		resource = Context.Buffer[Context.Offset] == '-' ? -1.0 : 1.0;

		Context.Offset++;
		resource *= MINUS();
		if (IsError())
			return 0;
		return resource;
	}
	resource *= STEPEN();
	if (IsError())
		return 0;
	return resource;

}

static double STEPEN(void)
{

	double base, exp;
	//go to functions 
	base = FUNCTIONS();

	if (IsError() )
		return 0;
	//search for"^" and calculate 
	if (Context.Buffer[Context.Offset] == '^')
	{

		Context.Offset++;

		exp = MINUS();
		if (IsError())
			return 0;

		if (base < 0 && fabs(exp - (int) exp) > THRESHOLD)
		{

			SetError(Negative_base_pow);

			return 0;

		}

		else if (base == 0 && exp < 0)

		{
			SetError(Negative_exp_pow);

			return 0;
		}
		base = pow(base, exp);

		if (fabs(base) == HUGE_VAL)
		{

			SetError(value_pow_too_huge);

			return 0;
		}

	}

	return base;
}

char * GettingBrackets(char const *Buffer)
{
	int z = 1, i;

	//search if brackets is normal count 
	for (i = 1; i < (int) strlen(Buffer) && z != 0; i++)
	{
		if (Buffer[i] == ')')
			z--;
		else if (Buffer[i] == '(')
			z++;

	}
	//if normal return char* to last bracket, else return 0
	if (Buffer[i - 1] != ')'|| (z>0))
		return NULL;
	else
		return (char *) Buffer + i - 1;
}


static double EvalucateBrackets(void)
{
	double resource;
	//if founs brackets, count if it is normal and calculate
	if (Context.Buffer[Context.Offset] == '(')
	{
		char *end;

		CONTEXT Saved;

		end = GettingBrackets(Context.Buffer + Context.Offset);
		if (end == NULL)
		{
			SetError(Missing_brackets);
			return 0;

		}
		*end = 0;

		Saved.Offset = end - Context.Buffer + 1;

		Saved.Buffer = Context.Buffer;

		

		
		//send char to calculator recursive 
		resource = Calculator(Context.Buffer + Context.Offset + 1);
		*end = ')';

		if (IsError()==no_memory)
			return 0;

		Context.Buffer = Saved.Buffer;

		Context.Offset = Saved.Offset;

		

		return resource;
	}
	return CONSTANTS();
}

//send to functions 
static double FUNCTIONS(void)
{
	return ApplyFunction(&Context, EvalucateBrackets);
}


//search for pi and e or for number 
static double CONSTANTS(void)
{
	char *end;
	int length;
	double resource;

	

	if (Context.Buffer[Context.Offset] == 'e' && !isalnum(Context.Buffer[Context.Offset + 1]))
	{
		Context.Offset++;
		return CONST_E;
	}

	if (Context.Buffer[Context.Offset] == 'p' && Context.Buffer[Context.Offset + 1] == 'i' && !isalnum(Context.Buffer[Context.Offset + 2]))
	{
		Context.Offset += 2;
		return CONST_PI;
	}
	//if found variable return its value 
	if ((length = GettingVariables(Context.Buffer + Context.Offset, &resource)) != 0)
	{
		Context.Offset+=length;
		return resource;
	}
	resource = strtod(Context.Buffer + Context.Offset, &end);
	if (end - (Context.Buffer + Context.Offset) == 0)
		SetError(Syntax_error);

	Context.Offset += end - (Context.Buffer + Context.Offset);

	return resource;
}




//cut all spaces 
static void PROBELI(void)
{
	int i, a, b;
	//if there is two numbers with no +-*/^ its an error
	for (i = 1; i < (int) strlen(Context.Buffer) - 1; i++)
		if (IS_SPACE(Context.Buffer[i]))
		{
			a = i - 1;
			b = i + 1;

			while (IS_SPACE(Context.Buffer[a]))
				a--;
			while (IS_SPACE(Context.Buffer[b]))
				b++;

			if (isalnum(Context.Buffer[a]) && isalnum(Context.Buffer[b]))
			{
				SetError(Syntax_error);
				return;
			}
		}
	//removing space 
	for (i = 0; i < (int) strlen(Context.Buffer); i++)
		if (IS_SPACE(Context.Buffer[i]))
		{
			memmove(Context.Buffer + i, Context.Buffer + i + 1, strlen(Context.Buffer + i + 1) + 1);
			i--;
		}
}







