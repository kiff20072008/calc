//standart .h
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
//local .h
#include "functions.h"
#include "error.h"


double(*EvalucateBrackets)(void);

FUNCTIONDESCRIPTION Functions[] =
{
	{ "default", FunctionDefault },
	{ "ln", FunctionLn },
	{ "log", FunctionLogarifm },
	{ "sqrt", FunctionSqrt },
	{ "ceil", FunctionCeil },
	{ "floor", FunctionFloor },
	{ "sin", FunctionSin },
	{ "cos", FunctionCos },
	{ "ctg", FunctionCotg },
	{ "tg", FunctionTg },
	{ "arcsin", FunctionArcsin },
	{ "arccos", FunctionArccos },
	{ "arctg", FunctionArctg }
};


static double FunctionDefault(CONTEXT *Context)
{
	Context->Offset += 0;
	return EvalucateBrackets();
}
static double FunctionLn(CONTEXT *Context)
{
	double resource;
	Context->Offset += 2;
	resource = EvalucateBrackets();
	if (resource <= 0)
	{
		SetError(base_logarifm_negative);
      return 0;
	}
	else
		return log(resource);
}

static double FunctionLogarifm(CONTEXT *Context)
{
	double resourcea, resourceb;
	char *end;
	Context->Offset += 3;
	end = strchr(Context->Buffer, ',');
	if (end == NULL)
	{
		SetError(Syntax_error);
		return 0;
	}
	*end = ')';
	resourceb = EvalucateBrackets();
	*end = '(';
	Context->Offset--;
	resourcea = EvalucateBrackets();
	*end = ',';
	if (resourceb == 1)
	{
		SetError(exp_logarifm_is_one);
		return 0;
	}
	if (resourcea <= 0)
	{
		SetError(base_logarifm_negative);
		return 0;
	}
	if (resourceb <= 0)
	{
		SetError(exp_log_negative);
		return 0;
	}
	if (resourcea == 1)
		return 0;
	resourceb = log(resourceb);
	if (fabs(resourceb) > THRESHOLD)
		return log(resourcea) / resourceb;
	else
	{
		SetError(exp_log_negative);
		return 0;
	}
}

static double FunctionSqrt(CONTEXT *Context)
{
	double resource;

	Context->Offset += 4;
	resource = EvalucateBrackets();
	if (resource < 0)
	{
		SetError(sqrt_from_negative);
		return 0;
	}
	else
		return sqrt(resource);
}

static double FunctionCeil(CONTEXT *Context)
{
	double resource;

	Context->Offset += 4;
	resource = EvalucateBrackets();
	return ceil(resource);
}


static double FunctionFloor(CONTEXT *Context)
{
	double resource;

	Context->Offset += 5;
	resource = EvalucateBrackets();
	return floor(resource);
}


static double FunctionSin(CONTEXT *Context)
{
	double resource;

	Context->Offset += 3;
	resource = EvalucateBrackets();
	return sin(resource);
}

static double FunctionCos(CONTEXT *Context)
{
	double resource;

	Context->Offset += 3;
	resource = EvalucateBrackets();
	return cos(resource);
}

static double FunctionCotg(CONTEXT *Context)
{
	double resource;

	Context->Offset += 3;
	resource = tan(EvalucateBrackets());
	if (resource > THRESHOLD)
		return 1 / resource;
	else
	{
		SetError(value_cot_too_huge);
		return 1;
	}
}


static double FunctionTg(CONTEXT *Context)
{
	double resource;

	Context->Offset += 2;
	resource = EvalucateBrackets();
	return tan(resource);
}

static double FunctionArccos(CONTEXT *Context)
{
	double resource;

	Context->Offset += 6;
	resource = EvalucateBrackets();
	if (fabs(resource) <= 1)
		return acos(resource);
	else
	{
		SetError(arcsin_arg_too_huge);
		return 1 ;
	}
}

static double FunctionArcsin(CONTEXT *Context)
{
	double resource;

	Context->Offset += 6;
	resource = EvalucateBrackets();
	if (fabs(resource) <= 1)
		return asin(resource);
	else
	{
		SetError(arcsin_arg_too_huge);
		return 1;

	}
}



static double FunctionArctg(CONTEXT *Context)
{
	double resource;

	Context->Offset += 5;
	resource = EvalucateBrackets();
	return atan(resource);
}




static FUNCTIONDESCRIPTION GetFunction(char * Buffer)
{
	char *ch;
	int i;
	for (i = 0 ; i < (int) (sizeof( Functions ) / sizeof( Functions[0] )); ++i)
	  if ((( ch = strstr( Buffer, Functions[i].FunctionName )) != NULL ) && (!isalnum(*( Buffer + strlen( Functions[i].FunctionName )))))
	    if (ch == Buffer)
		  return Functions[i];
	return Functions[0];
}

double ApplyFunction(CONTEXT *Context, double(*FUNCSII)(void))
{
	FUNCTIONDESCRIPTION funcdesc;
	if (IsError())
		return 0;
	EvalucateBrackets = FUNCSII;
	funcdesc = GetFunction(Context->Buffer + Context->Offset);
	if (IsError() )
		return 0;
	return funcdesc.Function(Context);
}
