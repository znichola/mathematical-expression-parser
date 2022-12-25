#include "eval.h"

void	cleanup_tree(t_tree *tree)
{
	if (tree->right)
	{
		cleanup_tree(tree->right);
	}
	if (tree->left)
	{
		cleanup_tree(tree->left);
	}
	free(tree->tok);
}

