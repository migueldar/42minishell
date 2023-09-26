/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/26 19:47:24 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*isolate_cmd(t_command_l *command_l, int which)
{
	t_command_l	*head_cpy;
	t_command_l	*prev;
	t_command	*ret;

	head_cpy = command_l;
	prev = NULL;
	ret = NULL;
	while (head_cpy)
	{
		if (which == 0)
		{
			if (prev)
				prev->next = head_cpy->next;
			else
				command_l = head_cpy->next;
			ret = head_cpy->cmd;
			free(head_cpy);
			break ;
		}
		prev = head_cpy;
		head_cpy = head_cpy->next;
		which--;
	}
	return (ft_lstclear_cmd_l(&command_l), ret);
}
