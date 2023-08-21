# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 21:05:06 by mde-arpe          #+#    #+#              #
#    Updated: 2023/08/21 22:28:15 by lucia-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME := minishell

# Archivos fuente principales
SRCS := src/env/env_list.c \
        src/lexer/lexer.c \
        src/mains/main.c \
        src/mains/main_lucia_y_el_uranio.c \
        src/malloc/malloc_debug.c \
        src/parser/parser.c \
        src/parser/parser2.c \
        src/signals/signal_handle.c \
        src/splitter/splitter.c \
        src/tokenizer/tokenizer.c \
        src/utils/not_final_utils.c \
        src/utils/utils.c \
        src/utils/utils2.c

# CC CFLAGS ... .c -> .o

# Archivos objeto
OBJS := $(SRCS:%.c=objs/%.o)
OBJS += libft/libft.a

CC = gcc
# Ruta decompilacin
CFLAGS = -Wall -Wextra -Werror -I libraries -I libft -I /Users/$(USER)/.brew/opt/readline/include #-fsanitize=address
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline #-fsanitize=address


RM = /bin/rm -rf

# Reglas para construir el ejecutable y otros objetivos
all: $(NAME)

#crear la carpeta objs
	
objs:
	@mkdir -p	objs/src/env \
				objs/src/lexer \
				objs/src/mains \
				objs/src/malloc \
				objs/src/parser \
				objs/src/signals \
				objs/src/splitter \
				objs/src/tokenizer \
				objs/src/utils

#compilar src
objs/%.o: %.c | objs
	$(CC) $(CFLAGS) -c $< -o $@

#enlazar objetos a OBJS
$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

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

.PHONY: all clean fclean re fclean_nolib re_nolib malloc_debug
