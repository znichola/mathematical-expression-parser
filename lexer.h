#ifndef LEXER_H
 #define LEXER_H
 #include <stdlib.h>
 #include <ctype.h>
 #include "token.h"
 #include "parse_float.h"

t_token	*scan_token(char *str);

void	next_token(char **str);

t_token	*lexer(char **str);

#endif
