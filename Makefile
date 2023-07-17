NAME = minishell
SRCS = main.c
CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
RM = /bin/rm -rf
OBJS = $(SRCS:%.c=objs/%.o)

$(NAME): $(OBJS)
	cc $(OBJS) $(LDFLAGS) -o $(NAME)
all: $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all

objs:
	mkdir -p objs
objs/%.o: %.c objs
	cc $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
