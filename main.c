#include "eval.h"

int main(int argc, char **argv)
{
	char	*expr;
	int		action;
	t_value	n;
	t_tree	*tree;

	if (parse_args(argc, argv, &expr, &action) != 0)
	{
		return (1);
	}
	tree = 0;
	parse_expression(&argv[1], &tree);
	if (action == COMPUTE)
	{
		n = evaluate(tree);
		printf("%f\n", n);	
	}
	else
	{
		auto_print_tree(tree);
	}
	return (0);
}
