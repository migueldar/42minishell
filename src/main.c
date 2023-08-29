/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:53:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/29 04:50:19 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUCIA

#include "minishell.h"

// add history should not add empty lines
int main(int argc, char **argv, char **env)
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
	//delete later
	// t_env *e;
	// e = ft_calloc(16,1 );
	// e->content = ft_calloc(16,1 );
	// e->content->key = ft_strdup("z");
	// e->content->value = ft_strdup("a a");
	// ft_lstadd_back((t_list **) &enviroment, (t_list *) e);
	//end delete
	// ft_print_env(enviroment);
	if (!enviroment)
		return 1; //algun tipo de error de malloc
	while (1)
	{
		raw = readline("$> ");
		if (!raw)   // ctrl + D
			break ; // will have to free all
		if (!is_empty(raw))
			add_history(raw); //dont add empty lines
		expanded_list = complete_parser(raw, enviroment);
		executer(expanded_list, enviroment);
		ft_lstclear((t_list **) &expanded_list, (void (*)(void *)) free_cmd);
	}
	ft_lstclear((t_list **) &enviroment, (void (*)(void *)) free_env_var);
	clear_history();
}

#endif
