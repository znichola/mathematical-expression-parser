CC=gcc
CFLAGS= -Wall -Wextra

ifdef DEBUG
	$(CFLAGS) += -fsanitize=address
endif

SRCS = main.c \
evaluate.c \
lexer.c \
parse_float.c \
parser.c \
print.c

NAME = eval

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

fclean:
	rm -f $(NAME)

re: fclean all
