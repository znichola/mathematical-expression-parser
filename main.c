#include "eval.h"

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

		print_tree((t_pos){40, 2}, tree);
		printf("\033[20;0H");
		return (0);
		// print(tree);
		printf("\n");
		if (tok)
		{
			printf("%d %s\n", tok->type, argv[1]);
			printf("parse error\n");
		}
		else
		{
			
			n = evaluate(tree);
			printf("\n%f\n", n);
		}
	}
	return (0);
}