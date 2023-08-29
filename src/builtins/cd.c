/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/29 10:42:04 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_env *envi, t_string_l *args)
{
	int		value;

	value = 0;
	if (args == NULL)
	{
		value = chdir(ft_getenv(envi, "HOME"));
		if (value == -1)
			return ((ft_printerror(1, "cd: HOME not set", 1)), 0);
	}
	else
	{
		value = chdir(args->content);
		if (value == -1)
		{
			ft_printerror(1, "cd: ", 0);
			ft_printerror(2, args->content, 0);
			ft_printerror(2, ": ", 0);
			perror("");
		}
		return (1);
	}
	return (0);
}
