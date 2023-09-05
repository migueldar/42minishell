/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:08:55 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/05 20:06:33 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *envi)
{
	while (envi)
	{
		if (envi->content->value)
		{
			if (envi->content->value != '\0')
			printf("%s=%s\n", envi->content->key, envi->content->value);

		}
		envi = envi->next;
	}
	return (0);
}
