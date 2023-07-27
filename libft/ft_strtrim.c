/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:53:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/25 03:08:39 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_in_str(char const c, char const *str)
{
	while (*str)
		if (c == *(str++))
			return (1);
	return (0);
}

static int	num_chars(char const *s1, char const *set)
{
	const char	*start;

	if (!(*s1))
		return (0);
	while (c_in_str(*s1, set))
		if (!(*(++s1)))
			return (0);
	start = s1;
	while (*s1)
		s1++;
	s1--;
	while (c_in_str(*s1, set))
		s1--;
	s1++;
	return (s1 - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ret;
	char		*ret_cpy;
	const char	*start;

	if (!s1 || !set)
		return (NULL);
	ret = ft_calloc(num_chars(s1, set) + 1, 1);
	if (!ret)
		return (NULL);
	ret_cpy = ret;
	if (!(*s1))
		return (ret);
	while (c_in_str(*s1, set))
		if (!(*(++s1)))
			return (ret_cpy);
	start = s1;
	while (*s1)
		s1++;
	s1--;
	while (c_in_str(*s1, set))
		s1--;
	s1++;
	while (start != s1)
		*(ret++) = *(start++);
	return (ret_cpy);
}
