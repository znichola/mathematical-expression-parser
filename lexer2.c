#include "eval.h"

/**
 * This will make a new linked list of the found tokens.
 * It will be a doubly linked list that re-uses the t_tree struct
 * with left / right corresponding to the previous / next item in the list.
 */
t_tree	*tokenizer(char *str)
{
	t_tree	*start;
	t_tree	*current;

	start = NULL;
	while (1)
	{
		current = lexer2(&str);
		if (current == NULL)
			return (NULL);
		if (start == NULL)
		{
			start = current;
		}
		if (current->tok->type == end)
		{
			current->right = NULL;
			return (start);
		}
	}
}

t_token	*lexer2(char **str)
{
	t_token *tok;

	while (isspace(**str))
		(*str)++;
	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
	{
		perror(0);
		return (0);
	}
	if (**str == '\0')
		tok->type = end;
	else if (strchr(**str, SYMBOLS))
	{
		tok->type = symbol;
		tok->value.c = **str;
	}
	else if (isalpha(**str))
	{
		tok->type = value;
		tok->value.v = parse_float(str);
	}
	else
		// TODO: here we can add the code to detect multi character word as identifiers
		// either match agaist a dictionary of possibilities, like pi pow sqrt etc..
		// or single letter constants like e or G
		// or record the string to be used as a variable name
		// for now it's just invalid
		tok->type = invalid;
	(*str)++;
	return (tok);
}
