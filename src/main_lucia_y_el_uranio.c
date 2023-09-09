#ifdef LUCIA

#include "minishell.h"
#include "structs.h"

int	ft_what_builtin(t_string_l	*args, t_env **envi)
{
	while (args)
	{
		if (args->content && ft_strncmp(args->content, "cd", 3) == 0)
		{
			return (ft_cd(*envi, args->next));
		}
		if (args->content && ft_strncmp(args->content, "pwd", 4) == 0)
		{
			return (ft_pwd());
		}
		if (args->content && ft_strncmp(args->content, "env", 4) == 0)
		{
      		return (ft_env(*envi));
    	}
		if (args && ft_strncmp(args->content, "echo", 4) == 0)
		{
			return (ft_echo(args->next));
		}
		if (args && ft_strncmp(args->content, "export", 7) == 0)
		{
			return (ft_export(args->next, envi));
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

// int	main(int argc, char **argv, char **env)
// {
// 	int counter;
// 	t_string_l	*headcomando;
// 	t_env *enviroment;
// 	int co;

// 	co = 1;
// 	if (argc <= 1)
// 	{
// 		return (1);
// 	}
// 	enviroment = create_env_list(env);
// 	if (!enviroment)
//  		return (1);
// 	counter = 1;
// 	while (argv[counter])
// 		counter ++;
// 	counter -= 2;
// 	new_comando(&headcomando, argv[co]);
// 	printf("comando %s\n", headcomando->content);
// 	co ++;

// 	while (counter)
// 	{
// 		new_comando(&headcomando, argv[co]);
// 		printf("comando %s\n", headcomando->next->content);
// 		printf("counter %d\n", counter);
// 		counter --;
// 		co ++;
// 	}
// 	ft_what_builtin(headcomando, enviroment);
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
		// if (!is_empty(raw))
			ft_what_builtin(expanded_list->cmd->args, &enviroment);
		// executer
		ft_lstclear((t_list **) &expanded_list, (void (*)(void *)) free_cmd);
	}
	ft_lstclear((t_list **) &enviroment, (void (*)(void *)) free_env_var);
	clear_history();
}

#endif