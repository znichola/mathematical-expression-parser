#include "eval.h"

int main(int argc, char **argv)
{
	char	*expr;
	int		action;
	t_value	n;
	t_tree	*tree;
	t_token	*tok;

	if (parse_args(argc, argv, &expr, &action) != 0)
	{
		return (1);
	}
	tree = 0;
	if (parse_expression(&argv[1], &tree) != -1)
	{
		tok = scan_token(argv[1]);
    	if (tree == NULL || tok)
    	{
        	printf("Error while parsing tree\n");
        	return 1;
    	}
		if (action == COMPUTE)
		{
			n = evaluate(tree);
			printf("%f\n", n);	
		}
		else
		{
			auto_print_tree(tree);
		}
	}
	cleanup_tree(tree);
	return (0);
}
