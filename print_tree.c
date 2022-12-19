#include "eval.h"

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

static void	print_token(t_token *tok)
{
	// printf("%.5s\n%.5s\n%.5s\n", dict_type(tok), dict_category(tok), dict_name(tok));
	if (tok->type == value)
	{
		// printf(":%.1g", tok->value.v);
		printf("%.1g", tok->value.v);
		return ;
	}
	if (tok->type == operation)
	{
		printf("%.1s", dict_sign(tok));
		return ;
	}
	printf("%.1s", dict_type(tok));
}


static int	branch_size(char dir, int *count, t_tree *tree)
{
	if (dir == 'l' && tree->left != NULL)
	{
		*count += 1;
		branch_size(dir, count, tree->left);
	}
	else if (dir == 'r' && tree->right != NULL)
	{
		*count += 1;
		branch_size(dir, count, tree->right);
	}
	return (-1);
}

// TODO this does not always correctly acess the size of the tree.
// so there is overlap on some expressions.
static int	tree_size(t_tree *tree)
{
	int	left;
	int	right;

	left = 0;
	branch_size('l', &left, tree);
	right = 0;
	branch_size('r', &right, tree);
	return (left > right ? left : right);
}

static void print_connector(t_pos p, char dir, int depth)
{
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

	tok = tree->tok;
	size = 3;
	if (tok->type == operation)
	{
		printf("\033[%d;%dH", p.y, p.x);
		print_token(tok);

		printf("\033[%d;0H", p.y);
		size = get_tree_max_width(tree);
		printf("s:%d", get_tree_max_width(tree));
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
