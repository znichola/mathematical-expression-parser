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

t_tree	*create_node(t_token *new_token, t_tree *left, t_tree *right)
{
	t_tree	*new_node;

	new_node = factory(new_token);
	new_node->left = left;
	new_node->right = right;
	return	(new_node);
}

void	parse_expression(char **str, t_tree **left_tree)
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

void	parse_term(char **str, t_tree **left_tree)
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

void	parse_factor(char **str, t_tree **tree)
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
