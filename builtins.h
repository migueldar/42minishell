#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}t_env;

int ft_create_env_list(char **env);
void	ft_print_array_bi(char **array);


#endif