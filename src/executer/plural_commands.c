/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plural_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/28 19:37:19 by mde-arpe         ###   ########.fr       */
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
		close(aux.fdin_next);
		free(pid);
		if (handle_dups(aux.fdin, aux.fdout))
			(clear_child(env, NULL, NULL, NULL),
				ft_lstclear_cmd_l(&cmd), exit(1));
		to_exec = isolate_cmd(cmd, aux.counter);
		if (to_exec->args && is_builtin(to_exec->args->content))
		{
			sig_setter(SIG_DFL, 0);
			exit(handle_builtin(to_exec, env, 0));
		}
		childs_tasks(env, to_exec);
	}
	if (pid[aux.counter] > 0)
		(close(aux.fdout), close(aux.fdin));
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
	sig_setter(sig_handler_wait, 0);
	if (manage_child(env, cmd, crt_aux_s(0, -2, pipes[0][1], pipes[0][0]), pid))
		return (1);
	cnt = 1;
	while (cnt < ft_lstsize((t_list *) cmd) - 1)
	{
		pipe(pipes[1]);
		if (manage_child(env, cmd,
				crt_aux_s(cnt, pipes[0][0], pipes[1][1], pipes[1][0]), pid))
			return (kill_childs(pid, cnt), 1);
		swap_pipes(pipes);
		cnt++;
	}
	if (manage_child(env, cmd, crt_aux_s(cnt, pipes[0][0], -2, -2), pid))
		return (kill_childs(pid, cnt), 1);
	return (wait_all_free(pid, ft_lstsize((t_list *) cmd)));
}
