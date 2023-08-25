/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/25 15:17:06 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

// int	ft_cd(int argc, char **argv, char **env)
// {
// 	char	*pwd;
// 	int		value;
// 	int		counter;

// 	pwd = NULL;
// 	counter = 0;
// 	if (argc > 3)
// 		return (1);
// 	pwd = getcwd(pwd, 0);
// 	if (!env || pwd == NULL)
// 		return (1);
// 	if (pwd)
// 	{
// 		value = chdir(argv[2]);
// 		if (value == -1)
// 			return (1);
// 	}
// 	return (0);
// }
int	ft_cd(t_env *envi, t_string_l *args)
{
	char	*pwd;
	int		value;

	if (!envi)
		return (1);
	pwd = getcwd(NULL, 0);
	//    ¿alguna posibilidad de que args o args->content sea nulo?
	if (!pwd)
		return (1);
	args = args->next;
	if (args == NULL)
		value = chdir(getenv("HOME"));
	else
	{
		value = chdir(args->content);
	}
	if (value == -1)
	{
		free(pwd);
		return (1);
	}
	return (0);
}
