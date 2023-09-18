/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:00:36 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/18 21:23:46 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_getenv(t_env *envi, char *arr, int *status)
{
	*status = 0;
	while (envi)
	{
		if (ft_strncmp(envi->content->key, arr, ft_strlen(arr) + 1) == 0)
		{
			if (!envi->content->value)
				break ;
			return (ft_strdup(envi->content->value));
		}
		envi = envi->next;
	}
	return (*status = 1, NULL);
}

int	leng_env(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len ++;
		env = env->next;
	}
	return (len);
}
