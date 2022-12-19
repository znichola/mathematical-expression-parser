#ifndef EVAL_H
# define EVAL_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

// # include <unistd.h>

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

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

typedef struct s_tree
{
	t_token			*tok;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

//evaluate.c
t_value	evaluate(t_tree *tree);

//lexer.c
t_token	*scan_token(char *str);
void	next_token(char **str);
t_token	*lexer(char **str);

//parse_float.c
t_value parse_float(char **str);

//parser.c
t_tree	*factory(t_token *t);
t_tree	*create_node(t_token *new_token, t_tree *left, t_tree *right);
void	parse_expression(char **str, t_tree **left_tree);
void	parse_term(char **str, t_tree **left_tree);
void	parse_factor(char **str, t_tree **tree);

//print.c
void	print(t_tree *tree);

// print_tree.c
void	print_tree(t_pos p, t_tree *tree);

// tree_ops.c
int		get_tree_width(t_tree *tree, int level);
int		get_tree_height(t_tree *tree);
int		get_tree_max_width(t_tree *tree);

#endif