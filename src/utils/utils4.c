/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:07:43 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/28 18:03:48 by mde-arpe         ###   ########.fr       */
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

//counter acts as strlen
//status 1 if fail
long int	ft_atol(const char *str, int *status)
{
	int					minus;
	unsigned long int	ret;
	int					counter;

	ret = ((minus = 0, 0));
	counter = 0;
	if (!str[0])
		return (*status = 1, 0);
	if (*str == '-')
		minus = 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!(*str <= '9' && *str >= '0'))
			return (*status = 1, 0);
		ret = ret * 10 + (*str++ - '0');
		counter++;
	}
	if (counter > 19 || (ret > 0x7fffffffffffffff && !minus)
		|| (ret > 0x8000000000000000 && minus))
		return (*status = 1, 0);
	if (minus)
		ret *= -1;
	return (*status = 0, ret);
}
