/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:03:25 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 17:18:39 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	int		c;
	size_t	aux;

	if (!(*to_find))
		return ((char *) str);
	while (*str != 0 && n > 0)
	{
		aux = n;
		c = 0;
		while (*(str + c) == *(to_find + c) || *(to_find + c) == 0)
		{
			if (*(to_find + c) == 0)
				return ((char *) str);
			if (aux == 0)
				break ;
			aux--;
			c++;
		}
		str++;
		n--;
	}
	return (0);
}
