/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:04:09 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 03:17:17 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	int	ret;
	int	ret2;

	ret = ft_strlen(src) + ft_strlen(dest);
	ret2 = size + ft_strlen(src);
	if (size <= (unsigned int) ft_strlen(dest))
		return (ret2);
	while (*dest != 0)
	{
		dest++;
		size--;
	}
	while (*src != 0 && size > 1)
	{
		*dest = *src;
		src++;
		dest++;
		size--;
	}
	*(dest++) = 0;
	return (ret);
}
