CC=gcc
CFLAGS= -Wall -Wextra

DEBUG=1
FSAN=1

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

OBJS = $(SRCS:%.c=%.o)

NAME = eval

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lm -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

db: all
	lldb ./$(NAME)
