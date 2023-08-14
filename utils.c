/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:53:05 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/14 18:32:21 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_isoperator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	free_arr_2(void **fr)
{
	int	counter;

	if (fr)
	{
		counter = 0;
		while (fr[counter])
		{
			free(fr[counter]);
			counter++;
		}
		free(fr);
	}
}
