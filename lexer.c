#include "eval.h"

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
t_value f_negate(t_value x, t_value y)
{
	(void)y;
	return -x;
}

t_token *scan_token(char *str)
{
	return (lexer(&str));
}

void next_token(char **str)
{
	t_token *tok;

	tok = lexer(str);
	free(tok);
}

t_token *lexer(char **str)
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
				tok->value.c = **str;
			}
			(*str)++;
			return (tok);
		}
	}
}
