#ifdef LUCIA

#include "minishell.h"
#include "structs.h"
///# include "builtins.h"
//# include "libft.h"


// int	main(int argc, char **argv, char **env)
// {
// 	t_env	*envi;

// 	#ifdef	MALLOC_DEBUG
// 	atexit(leaks);
// 	#endif
	
// 	if (argc && **argv && **env)
// 	{
// 		envi = create_env_list(env);
// 		// ft_print_env(envi);
// 		if (ft_strncmp(argv[1], "pwd", 4) == 0 && ft_strlen(argv[1]) == 3)
// 			ft_pwd();
// 		// if (ft_strncmp(argv[1], "cd", 3) == 0 && ft_strlen(argv[1]) == 3)
// 		// 	ft_cd();
// 		ft_lstclear((t_list **) &envi, (void (*)(void	*)) free_env_var);
// 	}

// 	return (0);
// }

int	ft_what_builtin(t_string_l	*args, t_env *envi)
{
	while (args)
	{
		if (args->content && ft_strncmp(args->content, "cd", 3) == 0)
		{
			ft_cd(envi, args->next);			
			return (0);
		}
		if (args->content && ft_strncmp(args->content, "pwd", 4) == 0)
		{
			ft_pwd();
			return (0);
		}
		args = args->next;
	}


	return (0);
}

// int	new_comando(t_string_l	**head, char *argv)
// {
// 	t_string_l	*new;

// 	new = ft_calloc(sizeof(t_string_l *), 1);
// 	if (!new)
// 		return (1);
// 	new->content = ft_strdup(argv);
// 	if (!new->content)
// 		return (1);
// 	new->next = NULL;
// 		printf("aaaa\n");
// 	if(!*head)
// 	{
// 		printf("if\n");
// 		*head = new;
// 	}
// 	else
// 	{
// 		printf("else\n");
// 		(*head)->next = new;
// 		new->next = NULL;
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **env)
{
	char		*raw;
	t_env		*enviroment;
	t_command_l *expanded_list;
	

	#ifdef MALLOC_DEBUG
	atexit(leaks);
	#endif

	((void) argc, (void) argv);
	g_exit_status = ST_OK;
	sig_setter(sig_handler_interactive);
	enviroment = create_env_list(env);
	if (!enviroment)
		return (1); //algun tipo de error de malloc
	while (1)
	{
		raw = readline("$> ");
		if (!raw)   // ctrl + D
			break ; // will have to free all
		if (!is_empty(raw))
			add_history(raw); //dont add empty lines
		expanded_list = complete_parser(raw, enviroment);
		ft_what_builtin(expanded_list->cmd->args, enviroment);
		// executer
		// ft_lstclear((t_list **) &expanded_list, (void (*)(void *)) free_cmd);
	}
	ft_lstclear((t_list **) &enviroment, (void (*)(void *)) free_env_var);
	clear_history();
}

#endif