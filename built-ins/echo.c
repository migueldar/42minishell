/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:16:12 by root              #+#    #+#             */
/*   Updated: 2023/08/15 11:28:15 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins.h"

int	ft_search_n(char *str)
{
	while (*str && *str == 'n')
		str ++;
	if (*str)
		return (1);
	return (0);
}

int	ft_echo(char **argv)
{
	int	count;
	int	verif_n;
	int	salto_de_linea;

	salto_de_linea = 0;
	count = 2;
	if (argv[1])
	{
		while (ft_strncmp(argv[count], "-n", 2) == 0)
		{
			verif_n = ft_search_n(&argv[count][2]);
			if (verif_n == 1)
				break ;
			salto_de_linea = 1;
			count ++;
		}
		while (argv[count])
		{
			write(1, argv[count], ft_strlen(argv[count]));
			count ++;
		}
	}
	if (salto_de_linea == 0)
		write(1, "\n", 1);
	return (0);
}
