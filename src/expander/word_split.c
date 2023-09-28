/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:37:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/24 22:29:17 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//status 0 malloc fail
//status 1 ok
t_exp_l	*word_split(t_exp_str exp, int *status)
{
	t_exp_l		*ret;
	t_exp_l		*new_n;
	size_t		i;
	char		in_q;

	*status = 0;
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
	return (*status = 1, ret);
}
