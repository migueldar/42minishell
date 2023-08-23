/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 00:40:39 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/23 02:56:30 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	free(redir->where);
	free(redir);
}

void	free_cmd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		ft_lstclear((t_list **) &(cmd->args), free);
	if (cmd->redirs)
		ft_lstclear((t_list **) &(cmd->redirs), (void (*)(void *)) free_redir);
	free(cmd);
}

// return 1 means malloc error
char	add_redir(t_command *cmd, t_token *redir, t_token *word)
{
	t_redir_l	*new_n;

	new_n = ft_calloc(1, sizeof (t_redir_l));
	if (!new_n)
		return (1);
	new_n->redir = ft_calloc(1, sizeof (t_redir));
	if (!new_n->redir)
		return (free(new_n), 1);
	new_n->redir->where = ft_strdup(word->content);
	if (!new_n->redir->where)
		return (free(new_n->redir), free(new_n), 1);
	if (redir->flag == OP_IN)
		new_n->redir->flag = IN;
	else if (redir->flag == OP_HERE_DOC)
		new_n->redir->flag = HERE_DOC;
	else if (redir->flag == OP_OUT)
		new_n->redir->flag = OUT;
	else if (redir->flag == OP_APPEND)
		new_n->redir->flag = APPEND;
	ft_lstadd_back((t_list **) &(cmd->redirs), (t_list *) new_n);
	return (0);
}

// return 1 means malloc error
char	add_word(t_command *cmd, t_token *token)
{
	t_string_l	*new_n;

	new_n = ft_calloc(1, sizeof (t_string_l));
	if (!new_n)
		return (1);
	new_n->content = ft_strdup(token->content);
	if (!new_n->content)
		return (free(new_n), 1);
	ft_lstadd_back((t_list **) &(cmd->args), (t_list *) new_n);
	return (0);
}
