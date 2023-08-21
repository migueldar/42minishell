#include <minishell.h>
# include "builtins.h"
# include <libft.h>

int main(int argc, char **argv, char **env)
{
    t_env   *envi;

    if (argc && **argv)
    {
        envi = create_env_list(env);
		ft_print_env(envi);
	    ft_lstclear((t_list **) &envi, (void (*)(void	*)) free_env_var);
    }

    return(0);
}