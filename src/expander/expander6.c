/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 01:37:43 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/25 03:36:23 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote_switch2(char *in_q, t_exp_str *exp, int cnt)
{
	if (*in_q && (exp->content)[cnt] == *in_q && (exp->was_exp)[cnt] == '0')
		*in_q = 0;
	else if (!*in_q && ((exp->content)[cnt] == 0x22
		|| (exp->content)[cnt] == 0x27) && (exp->was_exp)[cnt] == '0')
		*in_q = (exp->content)[cnt];
	else
		return (0);
	return (1);
}

static char	*word_quote_removal(t_exp_str *exp)
{
	char	*ret;
	char	*aux;
	char	in_quote;
	size_t	counter;

	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	in_quote = 0;
	counter = 0;
	while ((exp->content)[counter])
	{
		if (!in_quote_switch2(&in_quote, exp, counter))
		{
			aux = protected_strcharjoin(ret, (exp->content)[counter]);
			free(ret);
			if (!aux)
				return (NULL);
			ret = aux;
		}
		counter++;
	}
	return (ret);
}

t_string_l	*quote_removal(t_exp_l *exp_l)
{
	t_string_l	*ret;
	t_string_l	*new_n;

	ret = NULL;
	while (exp_l)
	{
		new_n = ft_calloc(1, sizeof (t_string_l));
		if (!new_n)
			return (NULL);
		new_n->content = word_quote_removal(exp_l->content);
		if (!new_n->content)
			return (ft_lstclear((t_list **) &ret, free), free(new_n), NULL);
		ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		exp_l = exp_l->next;
	}
	return (ret);
}
