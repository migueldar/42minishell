/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/30 14:21:46 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_errors_cd(char *content)
{
	ft_printerror(1, "cd: ", 0);
	ft_printerror(2, content, 0);
	ft_printerror(2, ": ", 0);
	perror("");
}

int	ft_cd(t_env *envi, t_string_l *args)
{
	int		value;
	char	*get;

	value = 0;
	if (args == NULL)
	{
		get = ft_getenv(envi, "HOME");
		value = chdir(get);
		free(get);
		if (value == -1)
			return (perror("minishell: cd: "), 0);
	}
	else if (ft_strncmp(args->content, "", 2) == 0)
		return (0);
	else
	{
		value = chdir(args->content);
		if (value == -1)
		{
			ft_errors_cd(args->content);
			return (1);
		}
	}
	return (0);
}
