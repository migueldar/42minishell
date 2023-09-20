/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/20 13:06:16 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*fork_free_command_l(t_command_l **command_l, int which)
{
	int			counter;
	t_command	*fork_command;
	t_command_l	*head;

	counter = 0;
	head = *command_l;
	while (*command_l)
	{
		if (counter == which)
		{
			fork_command = (*command_l)->cmd;
			(*command_l)->cmd = NULL;
		}
		(*command_l) = (*command_l)->next;
		counter ++;
	}
	ft_lstclear_cmd_l(&head);
	return (fork_command);
}

int	single_cmd(t_command_l *cmd, t_env *env)
{
	//int		pid;
	char	*cmd_path;

	cmd_path = find_path(env, cmd->cmd->args->content);
	if (!cmd_path)
	{
		return (1);
	}
	// printf("%s\n", cmd_path);
	// else
	free(cmd_path);
	// pid = fork();
	// if (pid < 0)
	// 	return (1);
	// if (pid > 0)
	// {
	// 	//redirecciones
	// 	//verificar comando
	// 	//ejecutar
	// }
	// else
	// 	wait(NULL);
	return (0);
}
