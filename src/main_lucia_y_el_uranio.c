#ifdef LUCIA

#include "minishell.h"
# include "builtins.h"
# include "libft.h"


int main(int argc, char **argv, char **env)
{
    // t_env   *envi;

    #ifdef MALLOC_DEBUG
	atexit(leaks);
	#endif
    ft_pwd();

    if (argc && **argv && **env)
    {
        // envi = create_env_list(env);
		// ft_print_env(envi);
        // if (ft_strncmp(argv[1], "pwd", 4) == 0 && ft_strlen(argv[1]) == 3)
        // {

        // }
	    // ft_lstclear((t_list **) &envi, (void (*)(void	*)) free_env_var);
    }

    return (0);
}

#endif