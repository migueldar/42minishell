/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:53:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 21:18:12 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*raw;
	t_env		*enviroment;
	t_command_l	*expanded_list;

	((void) argc, (void) argv);
	g_exit_status = ST_OK;
	sig_setter(sig_handler_interactive, 1);
	enviroment = create_env_list(env);
	if (!enviroment && *env)
		return (1);
	while (g_exit_status < ST_EXIT)
	{
		raw = readline("$> ");
		if (!raw)
			break ;
		expanded_list = complete_parser(raw, enviroment);
		if (expanded_list)
		{
			g_exit_status = executer(expanded_list, &enviroment);
			ft_lstclear((t_list **) &expanded_list,
				(void (*)(void *)) free_cmd);
		}
	}
	ft_lstclear((t_list **) &enviroment, (void (*)(void *)) free_env_var);
	return ((unsigned char) g_exit_status);
}
