/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:07:43 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/16 20:36:54 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**string_l_to_array(t_string_l *arg)
{
	char	**ret;
	int		counter;

	ret = ft_calloc(ft_lstsize((t_list *) arg) + 1, 8);
	if (!ret)
		return (NULL);
	counter = 0;
	while (arg)
	{
		ret[counter] = ft_strdup(arg->content);
		if (!ret[counter])
		{
			free_arr_2((void **) ret);
			return (NULL);
		}
		counter++;
		arg = arg->next;
	}
	return (ret);
}

static int	env_size(t_env *arg)
{
	int	ret;

	ret = 0;
	while (arg)
	{
		if (arg->content->value)
			ret++;
		arg = arg->next;
	}
	return (ret);
}

char	**env_to_array(t_env *arg)
{
	char	**ret;
	char	*aux;
	int		counter;

	ret = ft_calloc(env_size(arg) + 1, 8);
	if (!ret)
		return (NULL);
	counter = 0;
	while (arg)
	{
		if (arg->content->value)
		{
			aux = ft_strjoin(arg->content->key, "=");
			if (!aux)
				return (free_arr_2((void **) ret), NULL);
			ret[counter] = ft_strjoin(aux, arg->content->value);
			free(aux);
			if (!ret[counter])
				return (free_arr_2((void **) ret), NULL);
			counter++;
		}
		arg = arg->next;
	}
	return (ret);
}
