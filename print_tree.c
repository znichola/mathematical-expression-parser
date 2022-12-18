#include "eval.h"

const char	*dict_type(t_token *tok)
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

const char	*dict_category(t_token *tok)
{
	static const char	*ret[3];
	int					index;

	index = tok->value.o.category;
	ret[0] = "additive";
	ret[1] = "multiplicative";
	ret[2] = "other";
	return (ret[index]);
}

const char	*dict_name(t_token *tok)
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

const char	*dict_sign(t_token *tok)
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

void	print_token(t_token *tok)
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

void	print_tree(t_pos p, t_tree *tree)
{
	t_token *tok;

	tok = tree->tok;
	if (tok->type == operation)
	{
		printf("\n");
		printf("(%d, %d)", p.x, p.y);
		// printf("\033[%d;%dH", p.x, p.y);
		// printf("\033[%dC", p.x);
		printf("\033[%dG", p.x);
		// printf("\033[%dA", p.y);
		print_token(tok);
		printf("\n");
		if (tree->left != NULL)
		{
			// printf("\033[%dA", p.y + 1);
			printf("\033[%dG/", p.x-1);
			// printf("/\n");
			print_tree((t_pos){p.x - 2, p.y + 2}, tree->left);
		}
		if (tree->right != NULL)
		{
			// printf(" R");
			// printf("\033[%dA", p.y + 1);
			printf("\033[%dG\\", p.x+1);
			// printf("\\\n");
			print_tree((t_pos){p.x + 2, p.y + 2}, tree->right);
		}
	}
	else if (tok->type == value)
	{
		// printf(" ->");
		// printf("(%d, %d) ", p.x, p.y);
		// printf("\033[%dC", p.x);
		printf("\n");
		// printf("(%d, %d)", p.x, p.y);
		printf("\033[%dG", p.x);
		print_token(tok);
		printf("\n");
		printf("\033[%dA", 2);
	}
}