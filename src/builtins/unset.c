/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:43:07 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/09 01:47:54 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_env_var_name(char *str)
{
	if (!str || !(ft_isalpha(*str) || *str == '_'))
		return (0);
	while (*str)
	{
		if (!(ft_isalnum(*str) || (*str == '_')))
			return (0);
		str++;
	}
	return (1);
}

static void	ft_errors_unset(char *content)
{
	write(2, "minishell: ", 11);
	write(2, "unset: ", 7);
	write(2, "`", 1);
	write(2, content, ft_strlen(content));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid indentifier\n", 24);
}

int	single_unset(t_env **env, char *var)
{
	t_env	*env_cpy;

	if (!valid_env_var_name(var))
	{
		ft_errors_unset(var);
		return (1);
	}
	env_cpy = *env;
	while (env_cpy)
	{
		if (!ft_strncmp(env_cpy->content->key, var, ft_strlen(var) + 1))
		{
			lst_delnode((t_list **) env, (t_list *) env_cpy,
				(void (*)(void *)) free_env_var);
			break ;
		}
		env_cpy = env_cpy->next;
	}
	return (0);
}

int	ft_unset(t_env **env, t_string_l *args)
{
	int	ret;

	ret = 0;
	while (args)
	{
		ret |= single_unset(env, args->content);
		args = args->next;
	}
	return (ret);
}
