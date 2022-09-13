#include "print.h"

void	print(t_tree *tree)
{
	t_token *tok;

	tok = tree->tok;
	switch(tok->type)
	{
		case operation:
			if (tok->value.o.name == n_negate)
			{
				printf("-(");
				print(tree->left);
				printf(")");
			}
			else
			{
				printf("(");
				print(tree->left);
				printf(")");
				switch (tok->value.o.name)
				{
					case n_plus:
						printf("+");
						break ;
					case n_minus:
						printf("-");
						break ;
					case n_multiply:
						printf("*");
						break ;
					case n_divide:
						printf("/");
						break ;
				}
				printf("(");
				print(tree->right);
				printf(")");
			}
			break ;
		case value:
			printf("%g", tok->value.v);
			break ;
	}
}
