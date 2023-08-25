/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/26 01:31:53 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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


//    ¿alguna posibilidad de que args o args->content sea nulo?

// if (value == -1)
//                 {
//                         write(2, "bash: cd: ", 11); 
//                         write(2, &argv[2][counter++], ft_strlen(argv[2]));
//                         write(2, ": ", 2);
//                         perror("");
//                         return(1);
//                 }

int	ft_cd(t_env *envi, t_string_l *args)
{
	int		value;

	value = 0;
	if (args == NULL)
	{
		value = chdir(ft_getenv(envi, "HOME"));
		if (value == -1)
			return ((ft_putendl_fd("cd: HOME not set", 2)), 0);
	}
	else
	{
		value = chdir(args->content);
		if (value == -1)
		{
			ft_putendl_n_fd("cd: ", 2, 0);
			ft_putendl_n_fd(args->content, 2, 0);
			ft_putendl_n_fd(": ", 2, 0);
			perror("");
			return (1);
		}
	}
	return (0);
}
