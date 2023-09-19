/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/19 21:03:17 by lucia-ma         ###   ########.fr       */
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


int	single_forked_cmd(t_env **env, t_command_l *cmd)
{
	int		pid;

	//if (find path(env, cmd->cmd->args->content)
	//{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid > 0)
		{
			//redirecciones
			handle_redirs(cmd->cmd->redirs);
			// printf("redir == %s\n", cmd->cmd->redirs->redir->where);
			printf("soy un hijo\n");
			ft_lstclear_cmd_l(&cmd);
			ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
			clear_history();
			//ejecutar
			//if no se ha podido verificar liberamos ¿en padre?
		}
		printf("soy el padre\n");
		wait(NULL);
		return(0);
	//}
	return (1);
}
