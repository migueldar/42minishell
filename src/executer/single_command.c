/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2024/06/23 18:20:31 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_child(t_env **env, t_command *cmd, char *arg1, char **arg2)
{
	if (env)
		ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
	if (cmd)
		free_cmd(cmd);
	if (arg1)
		free(arg1);
	if (arg2)
		free_arr_2((void **) arg2);
}

void	childs_tasks(t_env **env, t_command *cmd)
{
	char	*path;
	char	**argv;
	char	**envi;
	int		status;

	if (handle_redirs(cmd->redirs))
		(clear_child(env, cmd, NULL, NULL), exit(1));
	if (!cmd->args)
		exit(0);
	status = 1;
	path = find_path(*env, cmd->args->content, &status);
	if (!path)
		(clear_child(env, cmd, NULL, NULL), exit(status));
	argv = string_l_to_array(cmd->args);
	if (!argv)
		(clear_child(env, cmd, path, NULL), perror("minishell"), exit(1));
	envi = env_to_array(*env);
	if (!envi)
		(clear_child(env, cmd, path, argv), perror("minishell"), exit(1));
	clear_child(env, cmd, NULL, NULL);
	sig_setter(SIG_DFL, 0);
	execve(path, argv, envi);
	free_arr_2((void **) envi);
	clear_child(NULL, NULL, path, argv);
	exit((perror("minishell"), 127));
}

int	single_cmd(t_env **env, t_command_l *cmd)
{
	int			pid;
	int			stat;
	t_command	*to_exec;

	stat = 0;
	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	sig_setter(sig_handler_wait, 0);
	if (pid == 0)
	{
		to_exec = isolate_cmd(cmd, 0);
		childs_tasks(env, to_exec);
	}
	if (pid > 0)
	{
		wait(&stat);
		sig_setter(sig_handler_interactive, 1);
	}
	if (WIFSIGNALED(stat))
		return (WTERMSIG(stat) | 0x80);
	return (WEXITSTATUS(stat));
}
