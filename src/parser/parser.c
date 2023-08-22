/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:36:28 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/17 03:48:50 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

// return 1 malloc fail
// return 3 nothing after pipe
// return 4 syntax error near unexpected token
// return 5 means pipe found
static char	flag_handler(t_token_flag flag, t_token_l **toks, t_command *cmd)
{
	char	status;

	if (flag == WORD)
		status = add_word(cmd, (*toks)->token);
	else if (flag == OP_PIPE)
	{
		status = 5;
		if (!(*toks)->next)
			status = 3;
		*toks = (*toks)->next;
	}
	else
	{
		if (!(*toks)->next || (*toks)->next->token->flag != WORD)
			status = 4;
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
// status = 3 nothing after pipe
// status = 4 syntax error near unexpected token 
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
// status = 2 begin pipe
// status = 3 nothing after pipe
// status = 4 syntax error near unexpected token 
t_command_l	*parser(t_token_l *toks, char *status)
{
	t_command_l	*ret;
	t_command_l	*aux;

	ret = NULL;
	while (toks)
	{
		if (toks->token->flag == OP_PIPE)
			return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_cmd),
					*status = 2, NULL);
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

	status = 0;
	ret = parser(toks, &status);
	if (!ret)
	{
		if (status == 1)
			printf("Malloc fail\n");
		else if (status == 2)
			printf("Begin pipe\n");
		else if (status == 3)
			printf("Nothing after pipe\n");
		else if (status == 4)
			printf("syntax error near unexpected token redir\n");
		return (NULL);
	}
	return (ret);
}
