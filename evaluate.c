#include "evaluate.h"

t_value	evaluate(t_tree *tree)
{
	t_token		*tok;

	tok = tree->tok;
	if(tok->type == operation)
	{
		if (tok->value.o.name == n_negate)
			return -1 * evaluate(tree->left);
		else
			return tok->value.o.function(evaluate(tree->left), evaluate(tree->right));
	}
	else // tok->type supposed to be VALUE
	{
		return (tok->value.v);
	}
}
