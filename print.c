#include "print.h"

void	print(t_tree *tree)
{
	t_token *tok;

	tok = tree->tok;
	switch(tok->type)
	{
		case operation:
			if (tok->value.o == negate)
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
				switch (tok->value.o)
				{
					case plus:
						printf("+");
						break ;
					case minus:
						printf("-");
						break ;
					case multiply:
						printf("*");
						break ;
					case divide:
						printf("/");
						break ;
				}
				printf("(");
				print(tree->right);
				printf(")");
			}
			break ;
		case value:
			printf("%f", tok->value.v);
			break ;
	}
}
