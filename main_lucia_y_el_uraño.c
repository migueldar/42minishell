#include "minishell.h"
# include "builtins.h"
# include "libft/libft.h"

void leaks(void)
{
      system("leaks -q minishell");
}


/*void	*malloc(size_t n)
{
	static int cnt = 0;

	if (cnt == MALLOC_FAIL) {
		printf("len was %zu\n", n);
		return (NULL);
	}
	cnt++;
	return (calloc(n, 1));
}*/

int main(int argc, char **argv, char **env)
{
    t_env   *envi;

    if (argc && **argv)
    {
        envi = ft_create_env_list(env);
	    ft_lstclear ((t_list **) &envi, (void (*)(void	*)) free_env_var);
    }
        
    atexit(leaks);
    /*if (argc > 2 && ft_strncmp(argv[1], "echo ", 4) == 0)
    {
      	ft_echo(argv);
    }*/
    return(0);
}