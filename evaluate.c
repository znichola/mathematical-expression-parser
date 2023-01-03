#include "eval.h"

t_value	evaluate(t_tree *tree)
{
	t_token		*tok;

	tok = tree->tok;
	if(tok->type == operation)
	{
		switch(tok->value.c)
		{
			case '+':
				return (evaluate(tree->left) + evaluate(tree->right));
			case '*':
				return (evaluate(tree->left) * evaluate(tree->right));
			case '/':
				return (evaluate(tree->left) / evaluate(tree->right));
			case '^':
				return (pow(evaluate(tree->left), evaluate(tree->right)));
			default:
				if (!tree->right)
					return -1 * evaluate(tree->left);
				return evaluate(tree->left) - evaluate(tree->right);
		}
	}
	else // tok->type supposed to be VALUE
	{
		return (tok->value.v);
	}
}
