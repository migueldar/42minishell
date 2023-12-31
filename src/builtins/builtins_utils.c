/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:32:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 16:56:14 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

// take into account side effects that executing 
// exit in children may have for the global variable
static int	execute_builtin(t_string_l *args, t_env **env)
{
	if (!ft_strncmp(args->content, "echo", 5))
		return (ft_echo(args->next));
	if (!ft_strncmp(args->content, "cd", 3))
		return (ft_cd(*env, args->next));
	if (!ft_strncmp(args->content, "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(args->content, "export", 7))
		return (ft_export(env, args->next));
	if (!ft_strncmp(args->content, "unset", 6))
		return (ft_unset(env, args->next));
	if (!ft_strncmp(args->content, "env", 4))
		return (ft_env(*env));
	if (!ft_strncmp(args->content, "exit", 5))
		return (ft_exit(args->next));
	return (0);
}

int	handle_builtin(t_command *cmd, t_env **env, int single)
{
	int	in;
	int	out;
	int	ret;

	if (single)
	{
		in = dup(0);
		out = dup(1);
	}
	if (handle_redirs(cmd->redirs) == 0)
		ret = execute_builtin(cmd->args, env);
	else
		ret = 1;
	if (single)
	{
		dup2(in, 0);
		dup2(out, 1);
		close(in);
		close(out);
	}
	return (ret);
}
