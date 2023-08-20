#include "minishell.h"
# include "builtins.h"
# include "libft/libft.h"

int main(int argc, char **argv, char **env)
{
    t_env   *envi;

    if (argc && **argv)
    {
        envi = create_env_list(env);
		//ft_print_env(envi);
	    ft_lstclear((t_list **) &envi, (void (*)(void	*)) free_env_var);
		if(argv[1] && (ft_strncmp(argv[1], "echo ", 4) == 0))
		{
			argv ++;
			argv ++;
			return(ft_echo(argv));
		}

    }

    return(0);
}