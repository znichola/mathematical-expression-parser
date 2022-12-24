#include "eval.h"

static int	check_args(int argc, char **argv)
{
	if (argc < 2 || argc > 4)
		return (-1);
	if (argc == 3 && strcmp(argv[1], "-p") != 0)
		return (-1);
	return (0);
}

int	parse_args(int argc, char **argv, char **expr, int *action)
{
	if (check_args(argc, argv) != 0)
	{
		printf("usage: ./eval <expr> or ./eval -p <expr>\n");
		return (-1);
	}
	if (argc == 2)
	{
		*expr = argv[1];
		*action = COMPUTE;
	}
	else
	{
		*expr = argv[2];
		*action = PRINT_TREE;
	}
	return (0);
}