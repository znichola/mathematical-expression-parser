#include "lexer.h"

t_token *scan_token(char *str)
{
	return	(lexer(&str));
}

void	next_token(char **str)
{
	t_token	*tok;

	tok = lexer(str);
	free(tok);
}

t_token	*lexer(char **str)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	while (isspace(**str))
		(*str)++;
	if (**str == '\0')
	{
		free(tok);
		return (0);
	}
	if (**str == '(')
	{
		tok->type = parenthesis;
		tok->value.p = open;
	}
	else if (**str == ')')
	{
		tok->type = parenthesis;
		tok->value.p = close;
	}
	else if (**str == '-' && !isspace(*(*str + 1)))
	{
		tok->type = operation;
		tok->value.o = negate;
	}
	else if (**str == '+')
	{
		tok->type = operation;
		tok->value.o = plus;
	}
	else if (**str == '-')
	{
		tok->type = operation;
		tok->value.o = minus;
	}
	else if (**str == '*')
	{
		tok->type = operation;
		tok->value.o = multiply;
	}
	else if (**str == '/')
	{
		tok->type = operation;
		tok->value.o = divide;
	}
	if (isdigit(**str))
	{
		tok->type = value;
		tok->value.v = parse_float(*str);
		while (isdigit(**str))
			(*str)++;
		if (**str == '.')
			(*str)++;
		while (isdigit(**str))
			(*str)++;
		return (tok);
	}
	(*str)++;
	return (tok);
}

/*
int main(int argc, char **argv)
{
	char *str = argv[1];

	t_token	*tok;

	tok = lexer(&str);
	while (tok)
	{
		if (tok->type == value)
			printf("%f\n", tok->value.v);
		tok = lexer(&str);
	}
	return (0);
}
*/
