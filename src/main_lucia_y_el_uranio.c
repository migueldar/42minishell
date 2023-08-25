#ifdef LUCIA

#include "minishell.h"
///# include "builtins.h"
//# include "libft.h"


int	main(int argc, char **argv, char **env)
{
	t_env	*envi;

	#ifdef	MALLOC_DEBUG
	atexit(leaks);
	#endif
	
	if (argc && **argv && **env)
	{
		envi = create_env_list(env);
		// ft_print_env(envi);
		if (ft_strncmp(argv[1], "pwd", 4) == 0 && ft_strlen(argv[1]) == 3)
			ft_pwd();
		// if (ft_strncmp(argv[1], "cd", 3) == 0 && ft_strlen(argv[1]) == 3)
		// 	ft_cd();
		ft_lstclear((t_list **) &envi, (void (*)(void	*)) free_env_var);
	}

	return (0);
}

// int	ft_what_builtin(t_command_l	*expanded_list, t_env *enviroment)
// {
// 	printf("%s\n", expanded_list->cmd->args->content);
// 	if (ft_strncmp(expanded_list->cmd->args->content, "cd", 3))
// 		ft_cd(enviroment, expanded_list->cmd->args);
// 	return(0);
// }

// int main(int argc, char **argv, char **env)
// {
// 	char		*raw;
// 	t_env		*enviroment;
// 	t_command_l *expanded_list;

// 	#ifdef MALLOC_DEBUG
// 	atexit(leaks);
// 	#endif
	
// 	((void) argc, (void) argv);
// 	g_exit_status = ST_OK;
// 	sig_setter(sig_handler_interactive);
// 	enviroment = create_env_list(env);
// 	// ft_print_env(enviroment);
// 	if (!enviroment)
// 		return 1; //algun tipo de error de malloc
// 	while (1)
// 	{
// 		raw = readline("$> ");
// 		if (!raw)   // ctrl + D
// 			break ; // will have to free all
// 		add_history(raw); //dont add empty lines
// 		expanded_list = complete_parser(raw, enviroment);
// 		printf("%s\n", expanded_list->cmd->args->content);
// 		ft_what_builtin(expanded_list, enviroment);
// 		// executer
// 		// ft_lstclear((t_list **) &expanded_list, (void (*)(void *)) free_cmd);
// 	}
// 	ft_lstclear((t_list **) &enviroment, (void (*)(void *)) free_env_var);
// 	clear_history();
// }

#endif