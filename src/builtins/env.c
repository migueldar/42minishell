/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:08:55 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/02 02:39:45 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *envi)
{
	while (envi)
	{
		if (envi->content->value)
			printf("%s=%s\n", envi->content->key, envi->content->value);
		envi = envi->next;
	}
	return (0);
}
