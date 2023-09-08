/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/08 18:45:32 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_env *envi, t_string_l *args)
{
	int		value;
	int		status;
	char	*where;

	status = 0;
	value = 0;
	if (!args)
	{
		where = ft_getenv(envi, "HOME", &status);
		if (!where && status == 1)
			return (write(2, "minishell: cd: HOME not set\n", 28), 1);
	}
	else
		where = ft_strdup(args->content);
	if (!where)
		return (perror("minishell"), 1);
	if (ft_strncmp(where, "", 1) != 0)
	{
		value = chdir(where);
		if (value == -1)
			return (ft_errors("cd: ", where, 1), free(where), 1);
	}
	free(where);
	return (0);
}
