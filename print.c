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

void	print_token2(t_token *t)
{
	printf("token : %14p type:", t);
	if (t == NULL)
		return ;
	switch (t->type)
	{
		case open:
			printf("close");
			break;
		case close:
			printf("close");
			break;
		case operation:
			printf("operation:%c", t->value.c);
			break;
		case value:
			printf("value %g", t->value.v);
			break;
		case symbol:
			printf("symbol %c", t->value.c);
			break;
		case identifier:
			printf("identifier");
			break;
		case invalid:
			printf("invalid");
			break;
		case end:
			printf("end");
			break;
		default:
			printf("not in list");
			break;
	}
	printf("\n\n");
}

void	print_token_list(t_tree *t)
{
	if (!t)
		return ;
	print_token2(t->tok);
	if (t->right)
		print_token_list(t->right);
}
