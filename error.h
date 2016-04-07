#ifndef _ERROR_H_
#define _ERROR_H_

typedef enum tag_ERROR
{
	No_error,
	Syntax_error,
	Negative_exp_pow,
	Negative_base_pow,
	Divide_by_zero,
	value_pow_too_huge,
	arcsin_arg_too_huge,
	arccos_arg_too_huge,
	base_logarifm_negative,
	exp_log_negative,
	Missing_brackets,
	Function_not_defined,
	value_cot_too_huge,
	sqrt_from_negative,
	variable_name_too_long,
	exp_logarifm_is_one,
	no_memory,
	wrong_simbol,
} ERROR;


void SetError(ERROR Err);
char * GetLastErrorDescription(void);
int IsError(void);

#endif