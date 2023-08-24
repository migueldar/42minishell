/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:37:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/24 04:19:42 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exp_str	*next_word(t_exp_str exp, size_t *cnt, char *in_quote)
{
	size_t		len;
	size_t		filler;
	t_exp_str	*ret;

	len = 0;
	ret = ft_calloc(1, sizeof(t_exp_str));
	if (!ret)
		return (NULL);
	while (exp.content[len + *cnt] && !(ft_isspace(exp.content[len + *cnt]) && !(*in_quote) && (exp.was_expanded)[len + *cnt] == '1'))
	{
		if (len > 0 && *in_quote && (exp.content)[len + *cnt] == *in_quote && (exp.was_expanded)[len + *cnt] == '0')
			*in_quote = 0;
		else if (len > 0 && !*in_quote && (((exp.content)[len + *cnt] == 0x22 || (exp.content)[len + *cnt] == 0x27) && (exp.was_expanded)[len + *cnt] == '0'))
			*in_quote = (exp.content)[len + *cnt];
		len++;
	}
	ret->content = ft_calloc(len + 1, 1);
	ret->was_expanded = ft_calloc(len + 1, 1);
	if (!ret->content || !ret->was_expanded)
		return (free(ret->content), free(ret->was_expanded), free(ret), NULL);
	filler = -1;
	while (++filler < len)
	{
		(ret->content)[filler] = (exp.content)[*cnt];
		(ret->was_expanded)[filler] = (exp.was_expanded)[*cnt];
		(*cnt)++;
	}
	return (ret);
}

t_exp_l	*word_split(t_exp_str exp)
{
	t_exp_l		*ret;
	t_exp_l		*new_n;
	size_t		counter;
	char		in_quote;

	ret = NULL;
	counter = 0;
	in_quote = 0;
	while ((exp.content)[counter])
	{
		if (in_quote && (exp.content)[counter] == in_quote && (exp.was_expanded)[counter] == '0')
			in_quote = 0;
		else if (!in_quote && (((exp.content)[counter] == 0x22 || (exp.content)[counter] == 0x27) && (exp.was_expanded)[counter] == '0'))
			in_quote = (exp.content)[counter];
		if (!(ft_isspace(exp.content[counter]) && !in_quote && (exp.was_expanded)[counter] == '1'))
		{			
			new_n = ft_calloc(1, sizeof (t_exp_l));
			if (!new_n)
				return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_env_var), NULL);
			new_n->content = next_word(exp, &counter, &in_quote);
			if (!new_n->content)
				return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_env_var), free(new_n), NULL);
			ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		}
		else
			counter++;
	}
	if (!ret)
	{
		ret = ft_calloc(1, sizeof(t_exp_l));
		ret->content = ft_calloc(1, sizeof(t_exp_str));
		ret->content->content = ft_strdup("");
		ret->content->was_expanded = ft_strdup("");
	}
	return (ret);
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
		if (in_quote && (exp->content)[counter] == in_quote && (exp->was_expanded)[counter] == '0')
			in_quote = 0;
		else if (!in_quote && ((exp->content)[counter] == 0x22 || (exp->content)[counter] == 0x27) && (exp->was_expanded)[counter] == '0')
			in_quote = (exp->content)[counter];
		else
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
			return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_env_var), free(new_n), NULL);
		ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		exp_l = exp_l->next;
	}
	return (ret);
}
