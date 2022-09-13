#ifndef PARSER_H
 #define PARSER_H

 #include "token.h"
 #include "lexer.h"
 #include <stdio.h>

typedef struct s_tree
{
	t_token			*tok;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

t_tree	*factory(t_token *t);

t_tree	*create_node(t_token *new_token, t_tree *left, t_tree *right);

void	parse_expression(char **str, t_tree **left_tree);

void	parse_term(char **str, t_tree **left_tree);

void	parse_factor(char **str, t_tree **tree);

#endif
