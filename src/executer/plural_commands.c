/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plural_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/26 17:33:08 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(int ***pipes_fd, int len)
{
	int	counter;

	counter = 0;
	(*pipes_fd) = malloc(len * sizeof(int *));
	if (!(*pipes_fd))
		return (1);
	while (len--)
	{
		(*pipes_fd)[counter] = malloc(2 * sizeof(int));
		if (!(*pipes_fd)[counter] || pipe((*pipes_fd)[counter]) < 0)
			return (1);
		counter ++;
	}
	return (0);
}

int	manage_pipes(int child, int **pipes_fd, int number_commands)
{
	if (child == 0)
		if (handle_dups(-2, pipes_fd[child][1]))
			return (1);
	if (child > 0 && child < number_commands)
		if (handle_dups(pipes_fd[child - 1][0], pipes_fd[child][1]))
			return (1);
	if (child == number_commands)
		if (handle_dups(pipes_fd[child - 1][0], -2))
			return (1);
	return (0);
}

void	kill_childs(int *pid, int position_childs)
{
	int	counter;

	counter = 0;
	while (position_childs)
	{
		kill(pid[counter], SIGKILL);
		position_childs --;
		counter ++;
	}
}

int	manage_pipes_and_forks(t_env **env, t_command_l	*cmd, int **pid2, int ***pipes_fd)
{
	int		position_child;
	int		*pid;

	pid = ((position_child = 0), *pid2);
	while (cmd)
	{
		pid[position_child] = fork();
		if (pid[position_child] < 0)
			return (kill_childs(pid, position_child), perror("minishell"), 1);
		if (pid[position_child] == 0)
		{
			if (manage_pipes(position_child, *pipes_fd,  cmd_size(cmd) - 1))
			{
				ft_lstclear_cmd_l(&cmd);
				ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
				clear_history();
				return (perror("minishell"), 1);
			}
			childs_tasks (env, cmd);
		}
		cmd = ((position_child ++), cmd->next);
	}
	return (0);
}

int	plural_commands(t_env **env, t_command_l *cmd)
{
	int	**pipes_fd;
	int	position_child;
	int	len;
	int	*pid;
	int	stat;

	position_child = 0;
	pipes_fd = NULL;
	len = cmd_size(cmd);
	pid = malloc(sizeof(int) * len);
	if (!pid || create_pipes(&pipes_fd, cmd_size(cmd) - 1))
		return (perror("minishell"), 1);
	if (manage_pipes_and_forks(env, cmd, &pid, &pipes_fd))
		return (1);
	while (len --)
		wait(&stat);
	return (WEXITSTATUS(stat));
}
