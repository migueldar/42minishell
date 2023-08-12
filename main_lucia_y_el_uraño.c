#include "minishell.h"
# include "builtins.h"
# include "libft/libft.h"


int main(int argc, char **argv, char **env)
{
    if(argc && **argv)
        ft_create_env_list(env);
    if (argc > 2 && ft_strncmp(argv[1], "echo ", 4) == 0)
    {
      	ft_echo(argv);
    }
    return(0);
}