/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 04:18:19 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/29 03:15:54 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if var doesnt exist in env returns ""
// returns null if malloc fails
static char	*expand_var(char *var, t_env *env)
{
	if (!var)
		return (NULL);
	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(g_exit_status));
	if (!ft_strncmp(var, "$", 2))
		return (ft_strdup("$"));
	while (env)
	{
		if (!ft_strncmp(var, env->content->key, ft_strlen(var) + 1))
			return (ft_strdup(env->content->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

//when enter here, $ is already gone
char	*expand_substring(char **str, t_env *env, char in_quote)
{
	char	*to_expand;
	char	*aux;
	char	*ret;

	if (ft_isalpha((*str)[0]) || (*str)[0] == '_')
	{
		to_expand = NULL;
		while (ft_isalnum(**str) || (**str == '_'))
		{
			aux = protected_strcharjoin(to_expand, **str);
			free(to_expand);
			if (!aux)
				return (NULL);
			to_expand = aux;
			(*str)++;
		}
		ret = expand_var(to_expand, env);
		free(to_expand);
		return (ret);
	}
	else if ((*str)[0] == '?')
		return ((*str)++, expand_var("?", env));
	else if (((*str)[0] == 0x22 || (*str)[0] == 0x27) && !in_quote)
		return (ft_strdup(""));
	return (expand_var("$", env));
}

static t_exp_str	expand_dollar(char **str, t_env *env,
						char in_quote, int *status)
{
	t_exp_str	ret;

	(*str)++;
	ret.content = expand_substring(str, env, in_quote);
	(*str)--;
	if (!ret.content)
		return (*status = 1, ret);
	ret.was_exp = full_string('1', ft_strlen(ret.content));
	if (!ret.was_exp)
		return (free(ret.content), *status = 1, ret);
	return (*status = 0, ret);
}

t_exp_str	expand_argument(char *str, t_env *env, int *status)
{
	t_exp_str	ret;
	t_exp_str	aux;
	t_exp_str	aux2;
	char		in_quote;

	init_to_zeros(&in_quote, &ret);
	while (*str)
	{
		in_quote = in_quote_switch(in_quote, *str);
		if (*str == '$' && in_quote != 0x27)
		{
			aux2 = expand_dollar(&str, env, in_quote, status);
			if (*status)
				return (free_exp_str(ret), ret);
			aux = protected_exp_join(ret, aux2.content, aux2.was_exp, 1);
			free_exp_str(aux2);
		}
		else
			aux = protected_exp_join(ret, str, "0", 0);
		free_exp_str(ret);
		if (!aux.content || !aux.was_exp)
			return (free_exp_str(aux), *status = 1, ret);
		ret = (str++, aux);
	}
	return (*status = 0, ret);
}
