#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "evaluate.h"
#include "print.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_value	n;
	t_tree	*tree;
	t_token	*tok;

	if (argc != 2)
	{
		printf("Error: program expects 1 argument.\n");
	}
	else
	{
		tree = 0;
		parse_expression(&argv[1], &tree);
		tok = scan_token(argv[1]);
		if (tok)
		{
			printf("parse error\n");
		}
		else
		{
			print(tree);
			n = evaluate(tree);
			printf("\n%f\n", n);
		}
	}
	return (0);
}
