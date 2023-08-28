/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:57:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/28 04:19:20 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// should return an status of wether it removed quotes or not
char	*quote_removal_heredoc(char *str)
{
	char	*ret;
	char	*aux;
	char	in_quote;

	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	in_quote = 0;
	while (str && *str)
	{
		if (!in_quote && (*str == 0x22 || *str == 0x27))
			in_quote = *str;
		else if (in_quote && *str == in_quote)
			in_quote = 0;
		else
		{
			aux = protected_strcharjoin(ret, *str);
			free(ret);
			if (!aux)
				return (NULL);
			ret = aux;
		}
		str++;
	}
	return (ret);
}

static t_redir	*heredocgoodluck() {return NULL;}

static t_redir	*redirdup(t_redir *todup)
{
	t_redir	*ret;

	ret = ft_calloc(1, sizeof(t_redir));
	if (!ret)
		return (NULL);
	ret->flag = todup->flag;
	ret->where = ft_strdup(todup->where);
	if (!ret->where)
		return (free(ret), NULL);
	return (ret);
}

static t_redir_l	*resolve_redirs_heredoc(t_redir_l *redirs)
{
	t_redir_l	*ret;
	t_redir_l	*new_n;

	ret = NULL;
	while (redirs)
	{
		new_n = ft_calloc(1, sizeof(t_redir_l));
		if (!new_n)
			return (ft_lstclear_redir_l(&ret), NULL);
		if (redirs->redir->flag != HERE_DOC)
			new_n->redir = redirdup(redirs->redir);
		else
			new_n->redir = heredocgoodluck();
		if (!new_n->redir)
			return (ft_lstclear_redir_l(&ret), free(new_n), NULL);
		ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		redirs = redirs->next;
	}
	return (ret);
}

// modifies the command list, converting << into <, opening the neccesary files
// returns status
int	resolve_heredocs(t_command_l *commands)
{
	t_redir_l	*aux;
	//int			status;

	while (commands)
	{
		aux = resolve_redirs_heredoc(commands->cmd->redirs);
		if (!aux && commands->cmd->redirs)
			return (1);
		ft_lstclear_redir_l(&(commands->cmd->redirs));
		commands->cmd->redirs = aux;
		commands = commands->next;
	}
	return (0);
}