#include <minishell.h>
# include "builtins.h"
# include <libft.h>

int main(int argc, char **argv, char **env)
{
    t_env   *envi;

    if (argc && **argv)
    {
        envi = create_env_list(env);
		//ft_print_env(envi);
        if(ft_strncmp(argv[1], "pwd", 3) == 0 && ft_strlen(argv[1]) == 3)
            ft_pwd(envi);
	    ft_lstclear((t_list **) &envi, (void (*)(void	*)) free_env_var);
    }

    return(0);
}