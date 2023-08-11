NAME = minishell
SRCS = main.c lexer.c utils.c splitter.c tokenizer.c
CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include #-fsanitize=address
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline #-fsanitize=address
RM = /bin/rm -rf
OBJS = $(SRCS:%.c=objs/%.o)
OBJS += libft/libft.a

$(NAME): objs $(OBJS)
	cc $(LDFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)
clean:
	$(RM) objs
	make fclean -C libft
fclean: clean
	$(RM) $(NAME)
re: fclean all

libft/libft.a: 
	make -C libft
objs:
	mkdir -p objs
objs/%.o: %.c
	cc $(CFLAGS) -c $< -o $@

#malloc debug flags#

fclean_nolib:
	$(RM) objs
	$(RM) $(NAME)
re_nolib: fclean_nolib all

malloc_debug:: CFLAGS += -D MALLOC_DEBUG
malloc_debug:: CFLAGS += -D MALLOC_FAIL=$(when)
malloc_debug: fclean_nolib objs $(OBJS) objs/malloc_debug.o
	cc $(LDFLAGS) $(OBJS) objs/malloc_debug.o -o $(NAME)

.PHONY: all clean fclean re fclean_nolib re_nolib malloc_debug
