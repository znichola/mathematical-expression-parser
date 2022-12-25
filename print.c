#include "eval.h"

void	print(t_tree *tree)
{
	t_token *tok;

	tok = tree->tok;
	switch(tok->type)
	{
		case operation:
			if (tok->value.c == '-' && !tree->right)
			{
				printf("-(");
				print(tree->left);
				printf(")");
			}
			else
			{
				printf("(");
				print(tree->left);
				printf(") %c (", tok->value.c);
				print(tree->right);
				printf(")");
			}
			break ;
		default:
			printf("%g", tok->value.v);
	}
}
