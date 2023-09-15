/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/15 16:49:11 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executer(t_command_l *cmds, t_env **env)
{
	int	status;

	status = resolve_heredocs(cmds, *env);
	//command_l_printer(cmds);
	if (status)
		return (1);
	if (ft_lstsize((t_list *) cmds) == 1)
	{
		if (cmds->cmd->args && is_builtin(cmds->cmd->args->content))
			return (handle_builtin(cmds, env, 1));
		else
		{
			return (0);
		}
	}
	else
	{
		
		t_command *jiji = fork_free_command_l(&cmds, 1);
		free_cmd(jiji);
	}
		
		// fork_free_command_l(&cmds, 11);
		// pipex(free_command_l);
			///dentro del pipex se mete cuando se haga el fork free_command_l
	// forker();
	return (0);
}
