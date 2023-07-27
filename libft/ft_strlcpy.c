/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:04:52 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 22:33:32 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	int	ret;

	ret = ft_strlen(src);
	while (*src && size > 1)
	{
		*(dest++) = *(src++);
		size--;
	}
	if (size > 0)
		*dest = 0;
	return (ret);
}
