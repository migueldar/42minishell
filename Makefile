NAME = minishell
SRCS = main.c lexer.c utils.c word_split.c tokenizer.c
CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
RM = /bin/rm -rf
OBJS = $(SRCS:%.c=objs/%.o)
OBJS += libft/libft.a

$(NAME): $(OBJS)
	cc $(OBJS) $(LDFLAGS) -o $(NAME)
all: $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
	make fclean -C libft
re: fclean all

libft/libft.a: 
	make -C libft
objs/%.o: %.c
	@mkdir -p objs
	cc $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
