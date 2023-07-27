/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:01:23 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 21:44:17 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	find;

	find = c;
	while (n > 0 && *((unsigned char *) s) != find)
	{
		n--;
		s++;
	}
	if (n == 0)
		return (0);
	return ((void *) s);
}
