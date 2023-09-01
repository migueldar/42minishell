/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:08:55 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/01 20:10:08 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_print_env(t_env *envi)
{
	while (envi)
	{
		printf("%s=%s\n", envi->content->key, envi->content->value);
		envi = envi->next;
	}
}