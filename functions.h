#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include "calculator.h"

double ApplyFunction(CONTEXT *Context, double(*Eval_Function)(void));
static double FunctionDefault(CONTEXT *Context);
static double FunctionLn(CONTEXT *Context);
static double FunctionLogarifm(CONTEXT *Context);
static double FunctionSqrt(CONTEXT *Context);
static double FunctionCeil(CONTEXT *Context);
static double FunctionFloor(CONTEXT *Context);
static double FunctionSin(CONTEXT *Context);
static double FunctionCos(CONTEXT *Context);
static double FunctionCotg(CONTEXT *Context);
static double FunctionTg(CONTEXT *Context);
static double FunctionArccos(CONTEXT *Context);
static double FunctionArcsin(CONTEXT *Context);
static double FunctionArctg(CONTEXT *Context);
typedef double (*FUNCTION_T) (CONTEXT *Context);


typedef struct tag_FUNCDESC
{
	char *FunctionName;
	FUNCTION_T  Function;
} FUNCTIONDESCRIPTION;



#endif