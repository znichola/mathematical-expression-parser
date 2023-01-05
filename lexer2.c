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
	t_tree	*previous;
	t_token	*tok;

	start = NULL;
	while (1)
	{
		// printf("added this toke: %c\n", *str);
		tok = lexer2(&str);
		if (tok == NULL)
			return (NULL);
		current = factory(tok);
		if (current == NULL)
			return (NULL);
		// end setup
		if (start == NULL)
		{
			start = current;
			previous = NULL;
		}
		print_token2(tok);
		if (current->tok->type == end)
			return (start);
		current->left = previous;
		if (previous != NULL)
			previous->right = current;
		// str++;
	}
}

t_token	*lexer2(char **str)
{
	t_token *tok;

	printf("tokenizing <%s>\n", *str);
	while (isspace(**str))
		(*str)++;
	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
	{
		perror(0);
		return (NULL);
	}
	if (**str == '\0')
		tok->type = end;
	else if (strchr(SYMBOLS, **str))
	{
		tok->type = symbol;
		tok->value.c = **str;
		(*str)++;
	}
	else if (isdigit(**str))
	{
		printf("found a float\n");
		tok->type = value;
		tok->value.v = parse_float(str);
	}
	else
		// TODO: here we can add the code to detect multi character word as identifiers
		// either match agaist a dictionary of possibilities, like pi pow sqrt etc..
		// or single letter constants like e or G
		// or record the string to be used as a variable name
		// for now it's just invalid
		// whatever this does, it would need to advance str
		tok->type = invalid;
	return (tok);
}
