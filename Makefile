# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 21:05:06 by mde-arpe          #+#    #+#              #
#    Updated: 2023/09/19 00:26:47 by lucia-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME := minishell

# Archivos fuente principales
SRCS := src/env/env_list.c \
		src/env/env_utils.c \
        src/main.c \
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
		src/utils/utils3.c \
		src/utils/utils4.c \
		src/expander/expander.c \
		src/expander/expander1.c \
		src/expander/expander2.c \
		src/expander/expander3.c \
		src/expander/expander4.c \
		src/expander/expander5.c \
		src/expander/expander6.c \
		src/builtins/pwd.c \
		src/builtins/export.c \
		src/builtins/echo.c \
		src/builtins/cd.c \
		src/builtins/env.c \
		src/builtins/unset.c \
		src/builtins/exit.c \
		src/builtins/export_utils.c \
		src/builtins/builtins_utils.c \
		src/executer/executer.c \
		src/executer/executer_utils.c \
		src/executer/here_doc.c \
		src/executer/here_doc_utils.c \
		src/executer/here_doc_unlink.c \
		src/executer/find_path.c \
		src/executer/redir.c \


# CC CFLAGS ... .c -> .o

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
				objs/builtins \
				objs/executer \

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
malloc_debug: $(OBJS) objs/debug/malloc_debug.o
	cc $(CFLAGS) -c src/debug/malloc_debug.c -o objs/debug/malloc_debug.o
	cc $(LDFLAGS) $(OBJS) objs/debug/malloc_debug.o -o $(NAME)

malloc_debug_sanitize:: CFLAGS += -fsanitize=address
malloc_debug_sanitize:: LDFLAGS += -fsanitize=address
malloc_debug_sanitize:: CFLAGS += -D MALLOC_DEBUG
malloc_debug_sanitize:: CFLAGS += -D MALLOC_FAIL=$(when)
malloc_debug_sanitize: fclean_nolib $(OBJS) objs/debug/malloc_debug.o
	cc $(LDFLAGS) $(OBJS) objs/debug/malloc_debug.o -o $(NAME)

#leaks flags#
leaks:: CFLAGS += -D LEAKS
leaks: $(OBJS) objs/debug/malloc_debug.o
	cc $(CFLAGS) -c src/main.c -o objs/main.o
	cc $(LDFLAGS) $(OBJS) objs/debug/malloc_debug.o -o $(NAME)

#sanitizer flags#
sanitize:: CFLAGS += -fsanitize=address -g3
sanitize:: LDFLAGS += -fsanitize=address
sanitize:: re_nolib

.PHONY: all clean fclean re fclean_nolib re_nolib malloc_debug sanitize lucia re_lucia leaks