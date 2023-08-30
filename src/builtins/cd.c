/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/31 01:53:07 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_errors_cd(char *content)
{
	ft_printerror(1, "cd: ", 0);
	ft_printerror(2, content, 0);
	ft_printerror(2, ": ", 0);
	perror("");
}

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
			return (ft_errors_cd(where), free(where), 1);
	}
	free(where);
	return (0);
}
