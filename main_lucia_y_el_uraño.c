#include "minishell.h"
# include "builtins.h"


int main(int argc, char **argv, char **env)
{
    argc = 1;
    if(argc && **argv)
        ft_create_env_list(env);
    return(0);
}