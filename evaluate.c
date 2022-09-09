#include "evaluate.h"

t_value	evaluate(t_tree *tree)
{
	t_token	*tok;

	tok = tree->tok;
	switch(tok->type)
	{
		case operation:
			switch(tok->value.o)
			{
				case plus:
					return (evaluate(tree->left)
							+ evaluate(tree->right));
				case minus:
					return (evaluate(tree->left)
							- evaluate(tree->right));
				case multiply:
					return (evaluate(tree->left)
							* evaluate(tree->right));
				case divide:
					return (evaluate(tree->left)
							/ evaluate(tree->right));
				case negate:
					return ((-1) * evaluate(tree->left));
			}
		case value:
			return (tok->value.v);
		default:
			printf("parse error: unexpected token\n");
			return (-1);
	}
}
