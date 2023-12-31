/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 05:01:05 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/24 22:49:51 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_redir_l(t_redir_l **tofree)
{
	ft_lstclear((t_list **) tofree, (void (*)(void *)) free_redir);
}

void	ft_lstclear_cmd_l(t_command_l **tofree)
{
	ft_lstclear((t_list **) tofree, (void (*)(void *)) free_cmd);
}

t_command_l	*expander_handler(t_command_l *cmds, t_env *env)
{
	int			status;
	t_command_l	*ret;

	status = 0;
	ret = expander(cmds, env, &status);
	if (!ret)
	{
		if (status == 1)
		{
			write(2, "minishell: ambigous redirect\n", 29);
			g_exit_status = ST_AMB_REDIR;
		}
		else
		{
			perror("minishell");
			g_exit_status = 1;
		}
		return (NULL);
	}
	return (ret);
}
