#ifndef TOKEN_H
 #define TOKEN_H

typedef enum e_token_type
{
	open,
	close,
	operation,
	value
} t_token_type;

typedef enum e_category
{
	additive,
	multiplicative,
	other
} t_category;

typedef enum e_name
{
	n_plus,
	n_minus,
	n_multiply,
	n_divide,
	n_negate
} t_name;

typedef double t_value;

typedef t_value (*t_function) (t_value, t_value);

typedef struct s_operation
{
	t_category	category;
	t_name		name;
 	t_function	function;
} t_operation;

typedef union u_token_value
{
	t_operation	o;
	t_value		v;	
} t_token_value;

typedef struct s_token
{
	t_token_type	type;
	t_token_value	value;	
}  t_token;

#endif
