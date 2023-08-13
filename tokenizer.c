/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:24:23 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/13 18:45:35 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_token(t_token *token)
{
	free(token->content);
	free(token);
}

t_token_l	*create_token_l(char *content)
{
	t_token_l	*ret;

	ret = ft_calloc(1, sizeof (t_token_l));
	if (!ret)
		return (NULL);
	ret->token = ft_calloc(1, sizeof (t_token));
	if (!ret->token)
		return (free(ret), NULL);
	ret->token->content = content;
	ret->token->flag = WORD;
	if (content[0] == '|')
		ret->token->flag = OP_PIPE;
	else if (content[0] == '<')
	{
		ret->token->flag = OP_IN;
		if (content[1] == '<')
			ret->token->flag = OP_HERE_DOC;
	}
	else if (content[0] == '>')
	{
		ret->token->flag = OP_OUT;
		if (content[1] == '>')
			ret->token->flag = OP_APPEND;
	}
	return (ret);
}

t_token_l	*tokenizer(t_string_l *input)
{
	t_token_l	*ret;
	t_token_l	*new_n;
	char		*dup;

	ret = NULL;
	while (input)
	{
		dup = ft_strdup(input->content);
		if (!dup)
			return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_token), NULL);
		new_n = create_token_l(dup);
		if (!new_n)
			return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_token), free(dup), NULL);
		ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		input = input->next;
	}
	return (ret);
}
	