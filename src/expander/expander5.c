/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:46:20 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/25 18:26:27 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	len_next_word(t_exp_str exp, size_t *cnt, char *in_quote)
{
	size_t		len;

	len = 0;
	while ((exp.content)[len + *cnt] && !(ft_isspace((exp.content)[len + *cnt])
			&& !(*in_quote) && (exp.was_exp)[len + *cnt] == '1'))
	{
		if (len > 0 && *in_quote && (exp.content)[len + *cnt] == *in_quote
			&& (exp.was_exp)[len + *cnt] == '0')
			*in_quote = 0;
		else if (len > 0 && !*in_quote && (((exp.content)[len + *cnt] == 0x22
				|| (exp.content)[len + *cnt] == 0x27)
				&& (exp.was_exp)[len + *cnt] == '0'))
			*in_quote = (exp.content)[len + *cnt];
		len++;
	}
	return (len);
}

t_exp_str	*next_word_ex(t_exp_str exp, size_t *cnt, char *in_quote)
{
	size_t		len;
	size_t		filler;
	t_exp_str	*ret;

	len = len_next_word(exp, cnt, in_quote);
	ret = ft_calloc(1, sizeof(t_exp_str));
	if (!ret)
		return (NULL);
	ret->content = ft_calloc(len + 1, 1);
	if (!ret->content)
		return (free(ret), NULL);
	ret->was_exp = ft_calloc(len + 1, 1);
	if (!ret->was_exp)
		return (free(ret->content), free(ret), NULL);
	filler = -1;
	while (++filler < len)
	{
		(ret->content)[filler] = (exp.content)[*cnt];
		(ret->was_exp)[filler] = (exp.was_exp)[*cnt];
		(*cnt)++;
	}
	return (ret);
}
