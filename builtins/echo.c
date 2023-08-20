/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:16:12 by root              #+#    #+#             */
/*   Updated: 2023/08/20 19:29:11 by lucia-ma         ###   ########.fr       */
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

void ft_print_echo(char **argv, int count)
{
	while (argv[count])
	{
		write(1, argv[count], ft_strlen(argv[count]));
		write(1, " ", 1);
		count ++;
	}
}

int	ft_echo(char **argv)
{
	int	count;
	int	verif_n;
	int	salto_de_linea;

	salto_de_linea = 0;
	count = 0;
	if (argv[0])
	{
		while (argv[count] && ft_strncmp(argv[count], "-n", 2) == 0)
		{
			verif_n = ft_search_n(&argv[count][2]);
			if (verif_n == 1)
				break ;
			salto_de_linea = 1;
			count ++;
		}
		if (argv[count])
			ft_print_echo(argv, count);
	}
	if (salto_de_linea == 0)
		write(1, "\n", 1);
	return (0);
}
