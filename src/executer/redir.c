/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 08:04:12 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/15 20:02:31 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_in_heredoc(int *fdin, char *file)
{
	if (*fdin != -2)
		close(*fdin);
	*fdin = open(file, O_RDONLY);
	if (*fdin == -1)
		return (1);
	return (0);
}

static int	redir_out_append(int *fdout, char *file, t_redir_flag flag)
{
	if (*fdout != -2)
		close(*fdout);
	if (flag == OUT)
		*fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*fdout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fdout == -1)
		return (1);
	return (0);
}

static int	handle_dups(int fdin, int fdout)
{
	if (fdin != -2)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
			return (perror("minishell"), close(fdin), close(fdout), 1);
		close(fdin);
	}
	if (fdout != -2)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("minishell"), close(fdout), 1);
		close(fdout);
	}
	return (0);
}

// in charge of unlinking all the files from heredoc
// return 0 if all ok
// return 1 some error, command musnt exec
int	handle_redirs(t_redir_l *redirs)
{
	int			fdin;
	int			fdout;
	t_redir_l	*recp;

	fdin = -2;
	fdout = -2;
	recp = redirs;
	while (redirs)
	{
		if (redirs->redir->flag == IN || redirs->redir->flag == HERE_DOC)
		{
			if (redir_in_heredoc(&fdin, redirs->redir->where))
				return (perror("minishell"), unlink_all_heredoc_redir(recp)
					, close(fdout), 1);
		}
		else
			if (redir_out_append(&fdout, redirs->redir->where,
					redirs->redir->flag))
				return (perror("minishell"), unlink_all_heredoc_redir(recp)
					, close(fdin), 1);
		redirs = redirs->next;
	}
	return (unlink_all_heredoc_redir(recp), handle_dups(fdin, fdout));
}
