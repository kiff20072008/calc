#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "error.h"
#include "variables.h"
double Calculator(char const *const BufferPtr);
char * GettingBrackets(char const *Buffer);
static double PLUS(void);
static double DELENIE(void);
static double STEPEN(void);
static double MINUS(void);
static double FUNCTIONS(void);
static double CONSTANTS(void);
static void PROBELI(void);

#define IS_SPACE(x) (((x) ==' ') || ((x)=='	'))
#define THRESHOLD 1e-10
#define CONST_E 2.718281828459045235360287471352
#define CONST_PI 3.141592653589793238462643383279


typedef struct tag_CONTEXT
{
	int Offset;
	char *Buffer;
} CONTEXT;


#endif 
