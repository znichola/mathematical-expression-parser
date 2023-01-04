#include "eval.h"

/*
static const char	*dict_type(t_token *tok)
{
	static const char	*ret[4];
	int					index;

	index = tok->type;
	ret[0] = "open";
	ret[1] = "close";
	ret[2] = "opperation";
	ret[3] = "value";
	return (ret[index]);
}

static const char	*dict_category(t_token *tok)
{
	static const char	*ret[3];
	int					index;

	index = tok->value.o.category;
	ret[0] = "additive";
	ret[1] = "multiplicative";
	ret[2] = "other";
	return (ret[index]);
}

static const char	*dict_name(t_token *tok)
{
	static const char	*ret[5];
	int					index;

	index = tok->value.o.name;
	ret[0] = "plus";
	ret[1] = "minus";
	ret[2] = "multiply";
	ret[3] = "divide";
	ret[4] = "negate";
	return (ret[index]);
}

static const char	*dict_sign(t_token *tok)
{
	static const char	*ret[5];
	int					index;

	index = tok->value.o.name;
	ret[0] = "+";
	ret[1] = "-";
	ret[2] = "*";
	ret[3] = "/";
	ret[4] = "-";
	return (ret[index]);
}

*/

static void	print_token(t_token *tok)
{
	// printf("%.5s\n%.5s\n%.5s\n", dict_type(tok), dict_category(tok), dict_name(tok));
	int	spacer;

	spacer = 3;
	if (tok->type == value)
	{
		spacer = snprintf(NULL, 0, "%.2g", tok->value.v);
		printf("\033[%dD%.2g", spacer / 2, spacer, tok->value.v);
		// printf("\033[100Dspcr:%d", snprintf(NULL, 0, "%.2g", tok->value.v));
		return ;
	}
	if (tok->type == operation)
	{
		printf("%c", tok->value.c);
		return ;
	}
	//printf("%2.3s", dict_type(tok));
}

static void print_connector(t_pos p, char dir, int depth)
{
	depth--;
	if (dir == 'l')
	{
		while (depth--)
		{
			printf("\033[%d;%dH/", p.y+1, p.x-1);
			p = (t_pos){p.x - 1, p.y + 1};
		}
	}
	else if (dir == 'r')
	{
		while (depth--)
		{
			printf("\033[%d;%dH\\", p.y+1, p.x+1);
			p = (t_pos){p.x + 1, p.y + 1};
		}
	}
}

void	print_tree(t_pos p, t_tree *tree)
{
	t_token *tok;
	int		size;
	// t_pos	t;

	tok = tree->tok;
	size = 3;
	if (tok->type == operation)
	{
		printf("\033[%d;%dH", p.y, p.x);
		print_token(tok);

		size = get_tree_max_width(tree);
		// printf("\033[%d;0H", p.y);
		// printf("s:%d", get_tree_max_width(tree));
		if (tree->left != NULL)
		{
			print_connector(p, 'l', size);
			print_tree((t_pos){p.x - size, p.y + size}, tree->left);
		}
		if (tree->right != NULL)
		{
			print_connector(p, 'r', size);
			print_tree((t_pos){p.x + size, p.y + size}, tree->right);
		}
	}
	else if (tok->type == value)
	{
		printf("\033[%d;%dH", p.y, p.x);
		print_token(tok);
	}
}

// wrapper for the print tree that
// calculates very roughly the space it needs
void	auto_print_tree(t_tree *tree)
{
	int	width;
	int	height;

	width = get_tree_max_width(tree) * 6;
	height = get_tree_height(tree) * 4;
	printf("\033[2J\033[1;1H");
	print_tree((t_pos){width, 2}, tree);
	printf("\033[%d;0H", height);
	printf("ans = %g", evaluate(tree));
	printf("\n");
}

// C99 compliant snprintf will accept NULL as buffer. and return the number of characters that would have been written.
// size_t len = snprintf(NULL,0,""Our data are : %d, %c, %x, %p", myint, mychar, myhex, mypointer);
