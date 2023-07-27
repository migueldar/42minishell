NAME = libft.a
SRC = ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c ft_memset.c ft_memcpy.c \
ft_memchr.c ft_memcmp.c ft_memmove.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strlen.c ft_strlcat.c \
ft_strncmp.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_bzero.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
FLAGS = -Wall -Wextra -Werror
RM = /bin/rm -f
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)

$(NAME): $(OBJ)
	gcc -c $(FLAGS) $(SRC)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)
clean:
	$(RM) $(OBJ)
fclean: clean clbonus
	$(RM) $(NAME)
re: fclean all
clbonus: 
	$(RM) $(OBJ) $(BONUS_OBJ)
bonus: $(OBJ) $(BONUS_OBJ)
	gcc -c $(FLAGS) $(SRC)
	ar rcs  $(NAME) $(OBJ) $(BONUS_OBJ)