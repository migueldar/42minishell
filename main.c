/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:53:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/19 01:08:36 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add history should not add empty lines
int main(int argc, char **argv, char **env)
{
	char		*raw;
	t_env		*enviroment;
	t_token_l	*tok_list;
	t_command_l	*parsed_list;
	t_command_l *expanded_list;
	
	#ifdef MALLOC_DEBUG
	atexit(leaks);
	#endif
	
	((void) argc, (void) argv);
	g_exit_status = ST_OK;
	sig_setter(sig_handler_interactive);
	enviroment = create_env_list(env);
	// ft_print_env(enviroment);
	if (!enviroment)
		return 1; //algun tipo de error de malloc
	while (1)
	{
		raw = readline("$> ");
		if (!raw)   // ctrl + D
			break ; // will have to free all
		add_history(raw);
		tok_list = lexer(raw);
		free(raw);
		if (!tok_list)
			continue ;
		parsed_list = parser_handler(tok_list);
		ft_lstclear((t_list **) &tok_list, (void (*)(void *)) free_token);
		if (!parsed_list)
			continue ;
		expanded_list = expander(parsed_list, enviroment);
		ft_lstclear((t_list **) &parsed_list, (void (*)(void *)) free_cmd);
	}
	ft_lstclear((t_list **) &enviroment, (void (*)(void *)) free_env_var);
	clear_history();
}
