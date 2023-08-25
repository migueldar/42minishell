/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:37:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/25 05:11:17 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exp_l	*empty_exp_l(void)
{
	t_exp_l	*ret;

	ret = ft_calloc(1, sizeof(t_exp_l));
	if (!ret)
		return (NULL);
	ret->content = ft_calloc(1, sizeof(t_exp_str));
	if (!ret->content)
		return (free(ret), NULL);
	ret->content->content = ft_strdup("");
	if (!ret->content->content)
		return (free(ret->content), free(ret), NULL);
	ret->content->was_exp = ft_strdup("");
	if (!ret->content->was_exp)
		return (free(ret->content->content), free(ret->content), free(ret),
			NULL);
	return (ret);
}

static void	init_word_split(t_exp_l **exp, size_t *i, char *in_quote)
{
	*exp = NULL;
	*i = 0;
	*in_quote = 0;
}

void	ft_lstclear_exp_l(t_exp_l **tofree)
{
	ft_lstclear((t_list **) tofree, (void (*)(void *)) free_env_var);
}

t_exp_l	*word_split(t_exp_str exp)
{
	t_exp_l		*ret;
	t_exp_l		*new_n;
	size_t		i;
	char		in_q;

	init_word_split(&ret, &i, &in_q);
	while ((exp.content)[i])
	{
		in_quote_switch2(&in_q, &exp, i);
		if (!(ft_isspace(exp.content[i]) && !in_q && (exp.was_exp)[i] == '1'))
		{			
			new_n = ft_calloc(1, sizeof (t_exp_l));
			if (!new_n)
				return (ft_lstclear_exp_l(&ret), NULL);
			new_n->content = next_word_ex(exp, &i, &in_q);
			if (!new_n->content)
				return (ft_lstclear_exp_l(&ret), free(new_n), NULL);
			ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		}
		else
			i++;
	}
	if (!ret)
		ret = empty_exp_l();
	return (ret);
}
