#ifndef PARSER_H
 #define PARSER_H

 #include "token.h"
 #include "lexer.h"
 #include <stdio.h>

typedef struct s_tree
{
	t_token		*tok;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

t_tree	*factory(t_token *t);

int	parse_expression(char **str, t_tree **left_tree);

int	parse_term(char **str, t_tree **left_tree);

int	parse_factor(char **str, t_tree **tree);

#endif
