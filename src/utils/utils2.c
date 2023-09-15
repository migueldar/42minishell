/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:22:36 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/15 16:08:06 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishel.h"
#include "utils.h"

void	ft_errors(char *function, char *content, int p)
{
	write(2, "minishell: ", 11);
	write(2, function, ft_strlen(function));
	write(2, content, ft_strlen(content));
	write(2, ": ", 2);
	if (p)
		perror("");
}

//return NULL if fail
//status 0 malloc fail
//status 1 not foun

// takes NULLS as len 0
char	*protected_strcharjoin(char *str, char c)
{
	char	*ret;
	int		counter;

	ret = ft_calloc(protected_strlen(str) + 2, 1);
	if (ret == NULL)
		return (NULL);
	counter = 0;
	while (str && str[counter])
	{
		ret[counter] = str[counter];
		counter++;
	}
	ret[counter] = c;
	return (ret);
}

int	is_empty(char const *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
