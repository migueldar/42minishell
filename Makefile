# Nombre del ejecutable
NAME = minishell

# Archivos fuente principales
SRCS = main_lucia_y_el_uranio.c lexer.c utils.c splitter.c tokenizer.c env_list.c utils2.c $(wildcard builtins/*.c)

# Directorio para objetos
OBJDIR = objs
BUILTINS_OBJDIR = $(OBJDIR)/builtins

# Archivos objeto
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
BUILTINS_OBJS = $(addprefix $(BUILTINS_OBJDIR)/, $(notdir $(wildcard builtins/*.c:.c=.o)))

# Rutas a las bibliotecas y opciones de cgit remoompilación
CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib

# Reglas para construir el ejecutable y otros objetivos
all: $(NAME)

$(NAME): $(OBJS) $(BUILTINS_OBJS)
	cc $(OBJS) $(BUILTINS_OBJS) -o $(NAME) $(LDFLAGS) -lreadline libft/libft.a

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	cc $(CFLAGS) -c $< -o $@

$(BUILTINS_OBJDIR)/%.o: builtins/%.c | $(BUILTINS_OBJDIR)
	cc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BUILTINS_OBJDIR):
	mkdir -p $(BUILTINS_OBJDIR)

# Limpieza de objetos y ejecutable
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

# Recompilación completa
re: fclean all

.PHONY: all clean fclean re
