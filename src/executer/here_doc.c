/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:57:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/29 04:39:59 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*temp_name()
{
	int		i;
	char	*itoaed;
	char	*name;
	
	i = -1;
	while (++i < 100000)
	{
		itoaed = ft_itoa(i);
		if (!itoaed)
			return (NULL);
		name = ft_strjoin("/tmp/minish-thd-", itoaed);
		free(itoaed);
		if (!name)
			return (NULL);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
	}
	return (NULL);
}

static char	*expand_heredoc(char *toexp, t_env *env)
{
	char	*ret;
	char	*aux;
	char	*aux2;

	ret = NULL;
	while (*toexp)
	{
		if (*toexp == '$')
		{
			toexp++;
			aux2 = expand_substring(&toexp, env, 1);
			toexp--;
			if (!aux2)
				return (free(ret), NULL);
			aux = protected_strjoin(ret, aux2);
			free(aux2);
		}
		else
			aux = protected_strcharjoin(ret, *toexp);
		free(ret);
		if (!aux)
			return (NULL);
		ret = (toexp++, aux);
	}
	return (ret);
}

//returns filename heredoc has written to
// debe recibir un status
static char	*execute_heredoc(char *del, t_env *env)
{
	int		fd;
	char	*exp_del;
	char	*file_name;
	char	*input;
	char	*exp_input;
	
	exp_del = quote_removal_heredoc(del);
	if (!exp_del)
		return (NULL);
	file_name = temp_name();
	if (!file_name)
		return (free(exp_del), NULL);
	fd = open(file_name, O_CREAT | O_EXCL | O_WRONLY);
	if (fd == -1)
		return (NULL);
	//add signals
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strncmp(input, exp_del, ft_strlen(input) + 1) == 0)
			break ;
		if (ft_strncmp(exp_del, del, ft_strlen(exp_del) + 1) == 0)
			exp_input = expand_heredoc(input, env);
		else
			exp_input = ft_strdup(input);
		free(input);
		if (!exp_input)
			return (free(input), free(exp_del), close(fd), NULL); 
		write(fd, exp_input, ft_strlen(exp_input));
		write(fd, "\n", 1);
		free(exp_input);
	}
	free(input);
	free(exp_del);
	close(fd);
	return (file_name);
}

static t_redir	*transform_heredoc(t_redir *redir, t_env *env)
{
	t_redir	*ret;

	ret = ft_calloc(1, sizeof(t_redir));
	if (!ret)
		return (NULL);
	ret->where = execute_heredoc(redir->where, env);
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
//status 1: unable to create file in /tmp
//status 2: open error
static t_redir_l	*resolve_redirs_heredoc(t_redir_l *redirs, t_env *env, int *status)
{
	t_redir_l	*ret;
	t_redir_l	*new_n;

	(void) status;
	ret = NULL;
	while (redirs)
	{
		new_n = ft_calloc(1, sizeof(t_redir_l));
		if (!new_n)
			return (ft_lstclear_redir_l(&ret), NULL);
		if (redirs->redir->flag != HERE_DOC)
			new_n->redir = redirdup(redirs->redir);
		else
			new_n->redir = transform_heredoc(redirs->redir, env);
		if (!new_n->redir)
			return (ft_lstclear_redir_l(&ret), free(new_n), NULL);
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

	status = 0;
	while (commands)
	{
		aux = resolve_redirs_heredoc(commands->cmd->redirs, env, &status);
		if (!aux && commands->cmd->redirs)
		{
			if (status == 1)
				write(2, "minishell: too many heredocs, \
					cannot create file in /tmp\n", 58);
			else if (status == 0 || status == 2)
				perror("minishell");
			return (status);
		}
		ft_lstclear_redir_l(&(commands->cmd->redirs));
		commands->cmd->redirs = aux;
		commands = commands->next;
	}
	return (0);
}
