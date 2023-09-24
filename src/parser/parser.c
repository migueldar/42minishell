/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:36:28 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/24 15:04:25 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_l	*malloc_command_l(void)
{
	t_command_l	*ret;

	ret = ft_calloc(1, sizeof (t_command_l));
	if (!ret)
		return (NULL);
	ret->cmd = ft_calloc(1, sizeof (t_command));
	if (!ret->cmd)
		return (free(ret), NULL);
	return (ret);
}

// return 1: malloc fail
// return 5 means pipe found
// return 0x20 | flag: syntax error near unexpected token
static char	flag_handler(t_token_flag flag, t_token_l **toks, t_command *cmd)
{
	char	status;

	if (flag == WORD)
		status = add_word(cmd, (*toks)->token);
	else if (flag == OP_PIPE)
	{
		status = ((*toks = (*toks)->next), 5);
		if (!(*toks))
			status = 0x20 | 0x6;
	}
	else
	{
		if (!(*toks)->next)
			status = 0x20 | 0x6;
		else if ((*toks)->next->token->flag != WORD)
			status = 0x20 | (*toks)->next->token->flag;
		else
		{
			status = add_redir(cmd, (*toks)->token, (*toks)->next->token);
			*toks = (*toks)->next;
		}
	}
	if (status == 0)
		*toks = (*toks)->next;
	return (status);
}

// return NULL means error
// status = 1 malloc fail
// status = 0x20 | flag: syntax error near unexpected token
t_command_l	*create_command_l(t_token_l **toks, char *status)
{
	t_command_l	*ret;

	ret = malloc_command_l();
	if (!ret)
		return (*status = 1, NULL);
	while (*toks)
	{
		*status = flag_handler((*toks)->token->flag, toks, ret->cmd);
		if (*status == 5)
			break ;
		else if (*status == 0)
			continue ;
		else
			return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_cmd),
					NULL);
	}
	return (ret);
}

// return NULL means error
// status = 1 malloc fail
// status = 0x20 | flag: syntax error near unexpected token
t_command_l	*parser(t_token_l *toks, char *status)
{
	t_command_l	*ret;
	t_command_l	*aux;

	ret = NULL;
	while (toks)
	{
		if (toks->token->flag == OP_PIPE)
			return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_cmd),
					*status = 0x20 | OP_PIPE, NULL);
		aux = create_command_l(&toks, status);
		if (!aux)
			return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_cmd),
					NULL);
		ft_lstadd_back((t_list **) &ret, (t_list *) aux);
	}
	return (*status = 0, ret);
}

t_command_l	*parser_handler(t_token_l *toks)
{
	char		status;
	t_command_l	*ret;
	char		*flag_error;

	status = 0;
	ret = parser(toks, &status);
	if (!ret)
	{
		g_exit_status = 1;
		if (status == 1)
			perror("minishell");
		else
		{
			flag_error = token_flag_to_str(status & 0x7);
			if (!flag_error)
				return (perror("minishell"), NULL);
			g_exit_status = ST_SYNTAX_ERROR;
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, flag_error, ft_strlen(flag_error));
			write(2, "'\n", 2);
			free(flag_error);
		}
		return (NULL);
	}
	return (ret);
}
