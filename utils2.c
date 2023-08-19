/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:22:36 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/19 01:11:33 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_array_bi(char **array)
{
	int	y;

	y = 0;
	while (array[y])
	{
		printf("array  ==  %s\n", array[y]);
		y ++;
	}
}

void	ft_print_env(t_env *envi)
{
	while (envi)
	{
		printf("%s=%s\n", envi->content->key, envi->content->value);
		envi = envi->next;
	}
}

// takes NULLS as len 0
char	*protected_strcharjoin(char *str, char c)
{
	char	*ret;
	int		counter;

	ret = ft_calloc(protected_strlen(str) + 2, 1);
	if (ret == NULL)
		return (NULL);
	counter = 0;
	while (str && str[counter])
	{
		ret[counter] = str[counter];
		counter++;
	}
	ret[counter] = c;
	return (ret);
}

/*void    ft_env(t_env *envi)
{
	while(envi)
	{
		printf("%s%s\n", envi->key, envi->value);
		envi = envi->next;
	}
}*/
