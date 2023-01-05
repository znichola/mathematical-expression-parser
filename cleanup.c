#include "eval.h"

void	cleanup_tree(t_tree *tree)
{
	if (!tree)
		return ;
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

void	cleanup_token_list(t_tree *list)
{
	if (!list)
		return ;
	if (list->right)
		cleanup_token_list(list->right);
	free(list->tok);
	free(list);
}
