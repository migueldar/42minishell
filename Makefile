# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 21:05:06 by mde-arpe          #+#    #+#              #
#    Updated: 2023/08/19 03:06:33 by mde-arpe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS =	main.c lexer.c utils.c utils2.c splitter.c tokenizer.c parser.c parser2.c not_final_utils.c \
		signal_handle.c env_list.c expander.c complete_parser.c
CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
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

#sanitizer flags#

sanitize:: CFLAGS += -fsanitize=address
sanitize:: LDFLAGS += -fsanitize=address
sanitize:: re_nolib


.PHONY: all clean fclean re fclean_nolib re_nolib malloc_debug
