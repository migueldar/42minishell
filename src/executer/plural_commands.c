/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plural_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 17:05:59 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_child(t_env **env, t_command_l *cmd, t_child_aux aux, int *pid)
{
	t_command	*to_exec;

	pid[aux.counter] = fork();
	if (pid[aux.counter] < 0)
		return (close(aux.fdin), close(aux.fdout), perror("minishell"), 1);
	if (pid[aux.counter] == 0)
	{
		if (handle_dups(aux.fdin, aux.fdout))
			(clear_child(env, NULL, NULL, NULL),
				ft_lstclear_cmd_l(&cmd), exit(1));
		to_exec = isolate_cmd(cmd, aux.counter);
		if (is_builtin(to_exec->args->content))
		{
			sig_setter(SIG_DFL);
			exit(handle_builtin(to_exec, env, 0));
		}
		childs_tasks(env, to_exec);
	}
	if (pid[aux.counter] > 0)
	{
		close(aux.fdin);
		close(aux.fdout);
	}
	return (0);
}

int	plural_commands(t_env **env, t_command_l *cmd)
{
	int	pipes[2][2];
	int	*pid;
	int	cnt;

	pid = malloc(sizeof(int) * ft_lstsize((t_list *) cmd));
	if (!pid)
		return (perror("minishell"), 1);
	pipe(pipes[0]);
	sig_setter(sig_handler_wait);
	if (manage_child(env, cmd, create_aux_struct(0, -2, pipes[0][1]), pid))
		return (1);
	cnt = 1;
	while (cnt < ft_lstsize((t_list *) cmd) - 1)
	{
		pipe(pipes[1]);
		if (manage_child(env, cmd,
				create_aux_struct(cnt, pipes[0][0], pipes[1][1]), pid))
			return (kill_childs(pid, cnt), 1);
		swap_pipes(pipes);
		cnt++;
	}
	if (manage_child(env, cmd, create_aux_struct(cnt, pipes[0][0], -2), pid))
		return (kill_childs(pid, cnt + 1), 1);
	return (wait_all_free(pid, ft_lstsize((t_list *) cmd)));
}
