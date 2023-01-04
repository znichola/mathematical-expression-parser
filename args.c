#include "eval.h"

static int	check_args(int argc, char **argv)
{
	// I think you mean 3 instead of 4 :D
	if (argc < 2 || argc > 3)
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
	if (expr == NULL || *expr == NULL || **expr == '\0')
	{
		printf("Error: Expression is NULL.\n");
		return (-1);
	}
	return (0);
}

/*
 * The getopt function could be used to parse options. -> maybe in future.
 while ((opt = getopt(argc, argv, "p")) != -1)
	{
		switch (opt) {
			case 'p':
				*action = PRINT_TREE;
				break;
			// check for invalid options
			default:
				printf("usage: ./eval <expr> or ./eval -p <expr>\n");
				return -1;
		}
	}
 */
 