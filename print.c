void	print(t_tree *tree)
{
	t_token *tok;

	tok = tree->tok;
	switch(tok->type)
	{
		case operation:
			if (tok->value.o == negate)
			{
				printf("-");

			}
			else
			{

			}
			break ;
	}
}
