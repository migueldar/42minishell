/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:22:36 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/28 20:22:37 by mde-arpe         ###   ########.fr       */
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

char	*ft_strjoinpath(char const *s1, char const *s2)
{
	char	*s;
	int		l;

	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = malloc((l + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (*s1)
		*s++ = *s1++;
	*s++ = '/';
	while (*s2)
		*s++ = *s2++;
	*s = 0;
	return (s - l);
}
