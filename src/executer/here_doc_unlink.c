/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_unlink.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 04:00:14 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/30 04:06:54 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_all_heredoc_redir(t_redir_l *first)
{
	while (first)
	{
		if (first->redir->flag == HERE_DOC)
			unlink(first->redir->where);
		first = first->next;
	}
}

void	unlink_all_heredoc_cmd(t_command_l *first, t_command_l *last)
{
	while (first != last)
	{
		unlink_all_heredoc_redir(first->cmd->redirs);
		first = first->next;
	}
}
