/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/24 22:30:38 by lucia-ma         ###   ########.fr       */
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

int	childs_tasks(char **envi, t_env **env, t_command_l *cmd)
{
	char	*arg1;
	char	**arg2;

	if (cmd->cmd->args)
	{
		arg1 = find_path(*env, cmd->cmd->args->content);
		arg2 = string_l_to_array(cmd->cmd->args);
		if (handle_redirs(cmd->cmd->redirs))
			return (1);
		ft_lstclear_cmd_l(&cmd);
		ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
		clear_history();
		if (execve(arg1, arg2, envi) == -1)
		{
			perror("minishell");
			exit(1);
		}
	}
	return (0);
}

int	single_cmd(t_command_l *cmd, t_env **env)
{
	char	**envi;
	int		pid;

	envi = env_to_array(*env);
	if (!envi)
		return (perror("minishell"), 1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (childs_tasks(envi, env, cmd))
		{
			ft_lstclear_cmd_l(&cmd);
			ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
			clear_history();
		}
	}
	if (pid > 0)
		wait (NULL);
	return (0);
}
