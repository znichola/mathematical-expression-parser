#include <ctype.h>
#include <stdlib.h>

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

typedef long double t_value;

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

t_value	parse_float(const char **str)
{
	t_value	n;
	t_value	sign;
	t_value	weight;

	n = 0;
	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (isdigit(**str))
	{
		n = (n * 10) + (**str - '0');
		(*str)++;		
	}
	if (**str == '.')
	{
		weight = 1;
		(*str)++;
		while (isdigit(**str))
		{
			weight *= 10;
			n += (**str - '0') * (1 / weight);
			(*str)++;
		}
	}
	return (n * sign);
}

t_value f_plus(t_value x, t_value y)
{
	return x + y;
}

t_value f_minus(t_value x, t_value y)
{
	return x - y;
}

t_value f_multiply(t_value x, t_value y)
{
	return x * y;
}

t_value f_divide(t_value x, t_value y)
{
	return x / y;
}

t_token *lexer(const char **str)
{
	t_token *tok;

	while (isspace(**str))
	{
		(*str)++;
	}
	if (**str == '\0')
	{
		return (0);
	}
	else
	{
		tok = malloc(sizeof(t_token));
		if (isdigit(**str))
		{
			tok->type = value;
			tok->value.v = parse_float(str);
			return (tok);
		}
		else
		{
			if (**str == '(')
			{
				tok->type = open;
			}
			else if (**str == ')')
			{
				tok->type = close;
			}
			else
			{
				tok->type = operation;
				if (**str == '+')
				{
					tok->value.o.category	= additive;
					tok->value.o.name		= n_plus;
					tok->value.o.function	= f_plus;
				}
				else if (**str == '-')
				{
					tok->value.o.category	= additive;
					tok->value.o.name		= n_minus;
					tok->value.o.function	= f_minus;
				}
				else if (**str == '*')
				{
					tok->value.o.category	= multiplicative;
					tok->value.o.name		= n_multiply;
					tok->value.o.function	= f_multiply;
				}
				else if (**str == '/')
				{
					tok->value.o.category	= multiplicative;
					tok->value.o.name		= n_divide;
					tok->value.o.function	= f_divide;
				}
			}
			(*str)++;
			return (tok);
		}
	}
}

t_token *scan_token(const char *str)
{
	return (lexer(&str));
}

void next_token(const char **str)
{
	t_token *tok;

	tok = lexer(str);
	free(tok);
}

typedef struct s_tree
{
	t_token			*tok;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

t_tree	*factory(t_token *t)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	new_node->tok = t;
	new_node->left = 0;
	new_node->right = 0;
	return (new_node);
}

t_tree	*create_node(t_token *new_token, t_tree *left, t_tree *right)
{
	t_tree	*new_node;

	new_node = factory(new_token);
	new_node->left = left;
	new_node->right = right;
	return	(new_node);
}

void	parse_term(const char **str, t_tree **left_tree);

void	parse_factor(const char **str, t_tree **tree);

void	parse_expression(const char **str, t_tree **left_tree)
{
	t_token *tok;
	t_tree	*right_tree;

	parse_term(str, left_tree);
	while (1)
	{
		tok = scan_token(*str);
		if (!tok || !(tok->type == operation && tok->value.o.category == additive))
			return ;
		else
		{
			next_token(str);
			parse_term(str, &right_tree);
			*left_tree = create_node(tok, *left_tree, right_tree);
		}
	}
}

void	parse_term(const char **str, t_tree **left_tree)
{
	t_token	*tok;
	t_tree	*right_tree;

	parse_factor(str, left_tree);
	while (1)
	{
		tok = scan_token(*str);
		if (!tok || !(tok->type == operation && tok->value.o.category == multiplicative))
			return ;
		else
		{
			next_token(str);
			parse_factor(str, &right_tree);
			*left_tree = create_node(tok, *left_tree, right_tree);
		}
	}
}

void	parse_factor(const char **str, t_tree **tree)
{
	t_token *tok;

	tok = scan_token(*str);
	next_token(str);
	if (tok->type == open)
	{
		parse_expression(str, tree);
		next_token(str); //supposed to correspond to token CLOSE
	}
	else if (tok->type == operation && tok->value.o.name == n_minus)
	{
		tok->value.o.name = n_negate;
		parse_factor(str, tree);
		*tree = create_node(tok, *tree, 0);
	}
	else if (tok->type == value)
	{
		*tree = factory(tok);
	}
}

t_value	evaluate(t_tree *tree)
{
	t_token		*tok;

	tok = tree->tok;
	if(tok->type == operation)
	{
		if (tok->value.o.name == n_negate)
			return -1 * evaluate(tree->left);
		else
			return tok->value.o.function(evaluate(tree->left), evaluate(tree->right));
	}
	else // tok->type supposed to be VALUE
	{
		return (tok->value.v);
	}
}

long double calculate (const char* expression) {
  t_value	n;
	t_tree	*tree;
	parse_expression(&expression, &tree);
	n = evaluate(tree);
	return (n);
}