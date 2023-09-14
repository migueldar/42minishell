/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:32:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/14 14:09:01 by lucia-ma         ###   ########.fr       */
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
int	execute_builtin(t_command_l *cmd, t_env **env)
{
	// redirs
	if (!ft_strncmp(cmd->cmd->args->content, "echo", 5))
		return (ft_echo(cmd->cmd->args->next));
	if (!ft_strncmp(cmd->cmd->args->content, "cd", 3))
		return (ft_cd(*env, cmd->cmd->args->next));
	if (!ft_strncmp(cmd->cmd->args->content, "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(cmd->cmd->args->content, "export", 7))
		return (ft_export(env, cmd->cmd->args->next));
	if (!ft_strncmp(cmd->cmd->args->content, "unset", 6))
		return (ft_unset(env, cmd->cmd->args->next));
	if (!ft_strncmp(cmd->cmd->args->content, "env", 4))
		return (ft_env(*env));
	if (!ft_strncmp(cmd->cmd->args->content, "exit", 5))
		return (ft_pwd());
	return (0);
}
