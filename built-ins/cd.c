/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:21:26 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/15 11:25:58 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"
#include "../builtins.h"

int	ft_cd(int argc, char **argv, char **env)
{
	char	*pwd;
	int		value;
	int		counter;

	counter = 0;
	if (argc > 3)
		write(2, "bash: cd: too many arguments\n", 29);
	pwd = get_pwd(env);
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

/*int main(int argc, char ** argv, char **env)
{
	if( argc >= 2 && ft_strncmp(argv[1], "cd", 2) == 0 && ft_strlen(argv[1]) == 2)
		ft_cd(argc, argv, env);
	return(0);

}*/