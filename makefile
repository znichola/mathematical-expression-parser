CC=gcc
# CFLAGS= -Wall -Wextra -Werror

# ifdef DEBUG
CFLAGS = -fsanitize=address -g3
# endif

SRCS = main.c \
evaluate.c \
lexer.c \
parse_float.c \
parser.c \
print.c \
print_tree.c

NAME = eval

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

fclean:
	rm -f $(NAME)

re: fclean all

db: all
	lldb ./$(NAME)
