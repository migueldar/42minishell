/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:01:51 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 18:35:39 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const void	*src_end;
	void		*dst_end;
	void		*dst_cpy;

	if (!dst && !src)
		return (NULL);
	src_end = src;
	dst_end = dst;
	dst_cpy = dst;
	while (len-- > 0)
	{
		src_end++;
		dst_end++;
	}
	while (src != src_end)
	{
		if (src < dst)
			*((char *)(--dst_end)) = *((char *)(--src_end));
		else
			*((char *)(dst++)) = *((char *)(src++));
	}
	return (dst_cpy);
}
