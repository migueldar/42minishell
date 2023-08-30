/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:57:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/30 04:45:39 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns filename heredoc has written to
static char	*execute_heredoc(char *del, t_env *env, int *status)
{
	int		fd;
	char	*exp_del;
	char	*fname;
	char	*input;
	char	*exp_i;

	exp_del = execute_heredoc_settup(del, &fd, &fname, status);
	if (!exp_del)
		return (NULL);
	while (1)
	{
		input = readline("> ");
		if (g_exit_status == ST_SIGINT_HEREDOC)
			return (*status = 1, unlink(fname), free(input),
				free(exp_del), free(fname), close(fd), NULL);
		if (!input || ft_strncmp(input, exp_del, ft_strlen(input) + 1) == 0)
			return (free(input), free(exp_del), close(fd), fname);
		if (ft_strncmp(exp_del, del, ft_strlen(exp_del) + 1) == 0)
			exp_i = expand_heredoc(input, env);
		else
			exp_i = ft_strdup(input);
		if ((free(input), !exp_i))
			return (unlink(fname), free(exp_del), free(fname), close(fd), NULL);
		free((write(fd, exp_i, ft_strlen(exp_i)), write(fd, "\n", 1), exp_i));
	}
}

static t_redir	*transform_heredoc(t_redir *redir, t_env *env, int *status)
{
	t_redir	*ret;

	ret = ft_calloc(1, sizeof(t_redir));
	if (!ret)
		return (NULL);
	sig_setter(sig_handler_here_doc);
	ret->where = execute_heredoc(redir->where, env, status);
	sig_setter(sig_handler_interactive);
	if (!ret->where)
		return (free(ret), NULL);
	ret->flag = redir->flag;
	return (ret);
}

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

//return NULL means fail
//status 0: malloc fail
//status 1: SIGINT_HEREDOC
//status 2: open error
//status 3: unable to create file in /tmp
static t_redir_l	*resolve_redirs_heredoc(t_redir_l *redirs,
											t_env *env, int *status)
{
	t_redir_l	*ret;
	t_redir_l	*new_n;
	t_redir_l	*redirs_head;

	ret = NULL;
	redirs_head = redirs;
	while (redirs)
	{
		new_n = ft_calloc(1, sizeof(t_redir_l));
		if (!new_n)
			return (unlink_all_heredoc_redir(ret),
				ft_lstclear_redir_l(&ret), NULL);
		if (redirs->redir->flag != HERE_DOC)
			new_n->redir = redirdup(redirs->redir);
		else
			new_n->redir = transform_heredoc(redirs->redir, env, status);
		if (!new_n->redir)
			return (unlink_all_heredoc_redir(ret),
				ft_lstclear_redir_l(&ret), free(new_n), NULL);
		ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		redirs = redirs->next;
	}
	return (ret);
}

// modifies the command list, converting the where attribute of all << redirs
// into tmp files the executer will read from
// returns status
int	resolve_heredocs(t_command_l *commands, t_env *env)
{
	t_redir_l	*aux;
	int			status;
	t_command_l	*cmds_head;

	status = 0;
	cmds_head = commands;
	while (commands)
	{
		aux = resolve_redirs_heredoc(commands->cmd->redirs, env, &status);
		if (!aux && commands->cmd->redirs)
		{
			unlink_all_heredoc_cmd(cmds_head, commands);
			if (status == 3)
				write(2, "minishell: heredoc: cant create file in /tmp\n", 46);
			else if (status == 0 || status == 2)
				perror("minishell");
			return (1);
		}
		ft_lstclear_redir_l(&(commands->cmd->redirs));
		commands->cmd->redirs = aux;
		commands = commands->next;
	}
	return (0);
}
