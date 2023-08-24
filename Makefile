# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 21:05:06 by mde-arpe          #+#    #+#              #
#    Updated: 2023/08/24 16:21:35 by lucia-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME := minishell

# Archivos fuente principales
SRCS := src/env/env_list.c \
        src/main.c \
        src/main_lucia_y_el_uranio.c \
        src/debug/malloc_debug.c \
        src/parser/parser.c \
        src/parser/parser2.c \
		src/parser/complete_parser.c \
        src/signals/signal_handle.c \
        src/lexer/lexer.c \
        src/lexer/splitter.c \
        src/lexer/tokenizer.c \
        src/utils/not_final_utils.c \
        src/utils/utils.c \
        src/utils/utils2.c \
		src/expander/expander.c \
		src/builtins/cd.c \

# Archivos objeto
OBJS := $(SRCS:src/%.c=objs/%.o)
OBJS += libft/libft.a

# Ruta decompilacin
CFLAGS = -Wall -Wextra -Werror -I lib -I libft -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

RM = /bin/rm -rf

# Reglas para construir el ejecutable y otros objetivos
all: $(NAME)

#crear la carpeta objs
objs:
	@mkdir -p	objs/env \
				objs/lexer \
				objs/debug \
				objs/parser \
				objs/signals \
				objs/utils \
				objs/expander \
				objs/builtins

#compilar src
objs/%.o: src/%.c | objs
	cc $(CFLAGS) -c $< -o $@

#enlazar objetos a OBJS
$(NAME): $(OBJS)
	cc $(LDFLAGS) $(OBJS) -o $(NAME)

#regla de compilacion libft
libft/libft.a: 
	make -C libft

#reglas de limpieza
clean:
	$(RM) objs
	make fclean -C libft
fclean: clean
	$(RM) $(NAME)
re: fclean all

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

#main lucia#
lucia:: CFLAGS += -D LUCIA
lucia:: all
re_lucia:: fclean_nolib lucia

.PHONY: all clean fclean re fclean_nolib re_nolib malloc_debug sanitize lucia re_lucia