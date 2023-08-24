/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/24 16:34:21 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

char	*get_pwd(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PWD=", 4) == 0)
			break ;
		env ++;
	}
	if (*env)
		return (*env + 4);
	return (NULL);
}

int	ft_cd(int argc, char **argv, char **env)
{
	char	*pwd;
	int		value;
	int		counter;

	pwd = NULL;
	counter = 0;
	if (argc > 3)
		return (write(2, "bash: cd: too many arguments\n", 29), 1);
	pwd = getcwd(pwd, 0);
	if (!env || pwd == NULL)
		return (1);
	if (pwd)
	{
		value = chdir(argv[2]);
		if (value == -1)
		{
			write(2, "bash: cd: ", 11);
			write(2, &argv[2][counter++], ft_strlen(argv[2]));
			write(2, ": ", 2);
			perror("");
			return (1);
		}
	}
	return (0);
}

