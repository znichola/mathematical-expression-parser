#include "eval.h"

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
		if (!tok)
		{
			printf("Panic: failed to allocate memory\n");
			exit(EXIT_FAILURE); //TODO maybe handle it more elegantly
		}
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
				// Check for invalid tokens :)
				if (**str != '+' && **str != '-' && **str != '*' && **str != '/')
				{
					tok->type = invalid;
					return (tok);
				}
				tok->type = operation;
				tok->value.c = **str;
			}
			(*str)++;
			return (tok);
		}
	}
}
