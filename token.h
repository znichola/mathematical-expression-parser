#ifndef TOKEN_H
 #define TOKEN_H

typedef enum e_token_type
{
	parenthesis,
	operation,
	value
} t_token_type;

typedef enum e_parenthesis
{
	open,
	close
} t_parenthesis;

typedef enum e_operation
{
	plus,
	minus,
	multiply,
	divide,
	negate
} t_operation;

typedef float t_value;

typedef union u_token_value
{
	t_parenthesis	p;
	t_operation	o;
	t_value		v;	
} t_token_value;

typedef struct s_token
{
	t_token_type	type;
	t_token_value	value;	
}  t_token;

#endif
