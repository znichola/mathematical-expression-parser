#include "parser.h"
#include "print.h"

t_tree	*factory(t_token *t)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	new_node->tok = t;
	new_node->left = 0;
	new_node->right = 0;
	return (new_node);
}

int	parse_expression(char **str, t_tree **left_tree)
{
	t_token *tok;
	t_tree	*right_tree;
	t_tree	*new_node;

	if (!parse_term(str, left_tree))
		return (0);
	while (1)
	{
		tok = scan_token(*str);
		if (!tok)
		{
			return (1);
		}
		else if ((tok->type == operation && tok->value.o == plus)
				|| (tok->type == operation && tok->value.o == minus))
		{
			next_token(str);
			right_tree = 0;
			if (!parse_term(str, &right_tree))
				return (0);
			new_node = factory(tok);
			new_node->left = *left_tree;
			new_node->right = right_tree;
			*left_tree = new_node;
		}
		else
		{
			return (1);
		}
	}
}

int	parse_term(char **str, t_tree **left_tree)
{
	t_token	*tok;
	t_tree	*right_tree;
	t_tree	*new_node;

	if (!parse_factor(str, left_tree))
		return (0);
	while (1)
	{
		tok = scan_token(*str);
		if (!tok)
		{
			return (1);
		}
		else if ((tok->type == operation && tok->value.o == multiply)
				|| (tok->type == operation && tok->value.o == divide))
		{
			next_token(str);
			right_tree = 0;
			if (!parse_factor(str, &right_tree))
				return (0);
			new_node = factory(tok);
			new_node->left = *left_tree;
			new_node->right = right_tree;
			*left_tree = new_node;
		}
		else
		{
			return (1);
		}
	}
}

int	parse_factor(char **str, t_tree **tree)
{
	t_token *tok;
	t_tree	*new_node;
	t_tree	*tmp_tree;

	tok = scan_token(*str);
	if (!tok)
	{
		printf("expected token\n");
		return (0);
	}
	else if (tok->type == parenthesis && tok->value.p == open)
	{
		next_token(str);
		tmp_tree = 0;
		if (!parse_expression(str, &tmp_tree))
			return (0);
		*tree = tmp_tree;
		tok = scan_token(*str);
		if (!tok || !(tok->type == parenthesis && tok->value.p == close))
		{
			printf("expected ')'\n");
			return (0);
		}
		next_token(str);
	}
	else if (tok->type == operation && tok->value.o == negate)
	{
		next_token(str);
		tmp_tree = 0;
		if (!parse_factor(str, &tmp_tree))
			return (0);
		new_node = factory(tok);
		new_node->left = tmp_tree;
		*tree = new_node;
	}
	else if (tok->type == value)
	{
		next_token(str);
		new_node = factory(tok);
		*tree = new_node;
	}
	else
	{
		printf("expected '(', '-' or value\n");
		return (0);
	}
}

/*
int main(int argc, char **argv)
{
	t_tree	*tree;
	char	*str;

	tree = 0;
	str = argv[1];
	parse_expression(&str, &tree);
	return (0);
}
*/
