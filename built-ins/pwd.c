/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:21:39 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/15 11:29:18 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins.h"

int	*ft_pwd(char **env)
{
	char	*pwd;

	pwd = get_pwd(env);
	if (pwd)
	{
		write(1, pwd ++, ft_strlen(pwd));
		write(1, "\n", 1);
	}
	return (0);
}

/*int main(int argc, char **argv, char **env)
{
	if(argc > 1)
	{
		if(ft_strncmp(argv[1], "pwd", 3) == 0 && ft_strlen(argv[1]) == 3)
			ft_pwd(env);
	}
	return (0);
}*/