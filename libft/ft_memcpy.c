/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:01:10 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 03:48:40 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	if (!dst && !src)
		return (ret);
	while (n > 0)
	{
		*((char *) dst) = *((char *) src);
		n--;
		dst++;
		src++;
	}
	return (ret);
}
