#ifdef LUCIA

#include "minishell.h"
# include "builtins.h"
# include "libft.h"


int main(int argc, char **argv, char **env)
{
    t_env   *envi;

    if (argc && **argv)
    {
        envi = create_env_list(env);
		ft_print_env(envi);
	    ft_lstclear((t_list **) &envi, (void (*)(void	*)) free_env_var);
    }

    if( argc >= 2 && ft_strncmp(argv[1], "cd", 2) == 0 && ft_strlen(argv[1]) == 2)
        ft_cd(argc, argv, env);

    return(0);
}

#endif