/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:32:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/02 08:12:45 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp_ignore_case(cmd, "echo", 5)
		|| !ft_strncmp_ignore_case(cmd, "cd", 3)
		|| !ft_strncmp_ignore_case(cmd, "pwd", 4)
		|| !ft_strncmp_ignore_case(cmd, "export", 7)
		|| !ft_strncmp_ignore_case(cmd, "unset", 6)
		|| !ft_strncmp_ignore_case(cmd, "env", 4)
		|| !ft_strncmp_ignore_case(cmd, "exit", 5))
		return (1);
	return (0);
}

int	execute_builtin(t_command_l *cmd, t_env **env)
{
	(void) cmd;
	(void) env;

	printf("in builtin\n");
	return (0);
}