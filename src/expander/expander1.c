/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 05:01:05 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/13 18:01:28 by lucia-ma         ###   ########.fr       */
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
			write(2, "minishell: ambigous redirect\n", 29);
		else
			perror("minishell");
		return (NULL);
	}
	return (ret);
}
