#include "error.h"

ERROR LastError;

//what error is 
static char *ErrorDesc[] =
{
	"No error",
	"Syntax error",
	"Negative exp of pow",
	"Negative base of pow",
	"Divide by zero",
	"value of pow too huge",
	"arcsin arg too huge",
	"arccos arg too huge",
	"base of logarifm is negative",
	"exp of log is negative",
	"Missing brackets",
	"Function not defined",
	"value of cot too huge",
	"sqrt from negative",
	"variable name too long",
	"exp logarifm is one",
	"no memory",
	"wrong simbol",
};


//return last error desription 
char * GetLastErrorDescription(void)
{
	return ErrorDesc[LastError];
}
//return if is error 
int IsError(void)
{
	return LastError;
}

//set error 
void SetError(ERROR Err)
{
	LastError = Err;
} 


