/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plural_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/26 20:49:55 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_childs(int *pid, int position_childs)
{
	int	counter;

	counter = 0;
	while (counter < position_childs)
	{
		kill(pid[counter], SIGKILL);
		counter++;
	}
}

int	wait_all(int *pid, int len)
{
	int	counter;
	int stat;

	counter = 0;
	while (counter < len)
	{
		waitpid(pid[counter], &stat, 0);
		counter++;
	}
	return (stat);
}

int	manage_child(t_env **env, t_command_l *cmd, int fdin, int fdout, int *pid, int counter)
{
	t_command	*to_exec;

	pid[counter] = fork();
	if (pid[counter] < 0)
		return (perror("minishell"), 1);
	if (pid[counter] == 0)
	{
		if (handle_dups(fdin, fdout))
			(clear_child(env, NULL, NULL, NULL), ft_lstclear_cmd_l(&cmd), exit(1));
		to_exec = isolate_cmd(cmd, counter);
		childs_tasks(env, to_exec);
	}
	return (0);
}

void	swap_pipes(int pipes[2][2])
{
	int	aux;

	aux = pipes[0][0];
	pipes[0][0] = pipes[1][0];
	pipes[1][0] = aux;
	aux = pipes[0][1];
	pipes[0][1] = pipes[1][1];
	pipes[1][1] = aux;
}

int	plural_commands(t_env **env, t_command_l *cmd)
{
	int	pipes[2][2];
	int	len;
	int	*pid;
	int	stat;
	int	counter;
	int	stat_chi;

	len = ft_lstsize((t_list *) cmd);
	pid = malloc(sizeof(int) * len);
	if (!pid)
		return (perror("minishell"), 1);
	pipe(pipes[0]);
	stat_chi = manage_child(env, cmd, -2, pipes[0][1], pid, 0);
	if (stat_chi)
		return (1);
	counter = 1;
	while (counter < len - 1)
	{
		pipe(pipes[1]);
		stat_chi = manage_child(env, cmd, pipes[0][0], pipes[1][1], pid, counter);
		if (stat_chi)
			return (kill_childs(pid, counter), 1);
		swap_pipes(pipes);
		counter++;
	}
	stat_chi = manage_child(env, cmd, pipes[0][0], -2, pid, counter);
	counter++;
	if (stat_chi)
		return (kill_childs(pid, counter), 1);
	stat = wait_all(pid, len);
	free(pid);
	return(WEXITSTATUS(stat));
}
