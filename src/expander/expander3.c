/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:04:54 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/24 21:31:18 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp_str(t_exp_str to_free)
{
	free(to_free.content);
	free(to_free.was_exp);
}

char	in_quote_switch(char in_quote, char curr)
{
	char	ret;

	ret = in_quote;
	if (in_quote && curr == in_quote)
		ret = 0;
	else if (!in_quote && (curr == 0x22 || curr == 0x27))
		ret = curr;
	return (ret);
}

//is_str = 1 :strjoin
//is_str = 0 :strcharjoin
t_exp_str	protected_exp_join(t_exp_str exp, char *cont,
									char *was_e, int is_str)
{
	t_exp_str	ret;

	if (is_str == 1)
	{
		ret.content = protected_strjoin(exp.content, cont);
		ret.was_exp = protected_strjoin(exp.was_exp, was_e);
	}
	else
	{
		ret.content = protected_strcharjoin(exp.content, *cont);
		ret.was_exp = protected_strcharjoin(exp.was_exp, *was_e);
	}
	return (ret);
}

void	init_to_zeros(char *str, t_exp_str *exp)
{
	*str = 0;
	exp->content = NULL;
	exp->was_exp = NULL;
}
