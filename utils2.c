/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:22:36 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/16 18:22:37 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		printf("%s%s\n", envi->content->key, envi->content->value);
		envi = envi->next;
	}
}

/*void    ft_env(t_env *envi)
{
	while(envi)
	{
		printf("%s%s\n", envi->key, envi->value);
		envi = envi->next;
	}
}*/
