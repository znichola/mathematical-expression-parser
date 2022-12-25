#include "eval.h"

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
		if (!tok || !(tok->type == operation && (tok->value.c == '+' || tok->value.c == '-')))
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

	if (parse_factor(str, left_tree) == -1)
        exit(EXIT_FAILURE); //TODO maybe handle it more elegantly
	while (1)
	{
		tok = scan_token(*str);
		if (!tok || !(tok->type == operation && (tok->value.c == '*' || tok->value.c == '/')))
			return ;
		else
		{
			next_token(str);
			if (parse_factor(str, &right_tree) == -1)
                exit(EXIT_FAILURE); //TODO maybe handle it more elegantly
			*left_tree = create_node(tok, *left_tree, right_tree);
		}
	}
}

int parse_factor(char **str, t_tree **tree)
{
    t_token *tok;

    tok = scan_token(*str);
    if (!tok) // check if scan_token returned a valid token
        return -1;
    next_token(str);
    if (tok->type == open)
    {
        parse_expression(str, tree);
        // Check if the next token is a close parenthesis
        tok = scan_token(*str);
        if (tok && tok->type == close)
            next_token(str);
        else
        {
            printf("Invalid expression: open parenthesis\n");
            return -1;
        }
    }
    else if (tok->type == operation && tok->value.c == '-')
    {
        if (parse_factor(str, tree) == -1)
            return -1;
        *tree = create_node(tok, *tree, 0);
    }
    else if (tok->type == value)
    {
        *tree = factory(tok);
    }
    return 0;
}
