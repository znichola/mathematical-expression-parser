#include "eval.h"

int main(int argc, char **argv)
{
	char	*expr;
	int		action;
	t_value	n;
	t_tree	*tree;
	t_token	*tok;
	int		status;

	if (parse_args(argc, argv, &expr, &action) != 0)
	{
		return (1);
	}
	tree = 0;
	if ((status = parse_expression(&expr, &tree)) != -1)
	// if ((status = parse_expression(&argv[1], &tree)) != -1)
	{
		tok = scan_token(expr);
		if (tree == NULL || tok)
		{
			printf("Error while parsing tree\n");
			status = 1;
		}
		else if (action == COMPUTE)
		{
			n = evaluate(tree);
			printf("%f\n", n);
		}
		else
		{
			auto_print_tree(tree);
		}
		free(tok);
	}
	cleanup_tree(tree);
	return (status);
}
