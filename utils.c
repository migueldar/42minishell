/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:53:05 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/18 20:02:36 by mde-arpe         ###   ########.fr       */
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

int	protected_strlen(char const *str)
{
	int	counter;

	counter = 0;
	while (str && str[counter])
		counter++;
	return (counter);
}

// takes NULLS as len 0
char	*protected_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		counter;

	ret = ft_calloc(protected_strlen(s1) + protected_strlen(s2) + 1, 1);
	if (ret == NULL)
		return (NULL);
	counter = -1;
	while (s1 && s1[++counter])
		ret[counter] = s1[counter];
	while (s2 && s2[++counter])
		ret[counter] = s2[counter - protected_strlen(s1)];
	return (ret);
}
