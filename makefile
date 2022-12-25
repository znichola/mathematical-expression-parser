CC=gcc
CFLAGS= -Wall -Wextra

ifdef DEBUG
	CFLAGS += -g3
endif

ifdef FSAN
	CFLAGS += -fsanitize=address
endif

SRCS = main.c \
evaluate.c \
lexer.c \
parse_float.c \
parser.c \
print.c \
print_tree.c \
tree_ops.c \
args.c \
cleanup.c

NAME = eval

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

fclean:
	rm -f $(NAME)

re: fclean all

db: all
	lldb ./$(NAME)
