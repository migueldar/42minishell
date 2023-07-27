/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:01:38 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/23 02:10:10 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0)
	{
		if (*(char *) s1 != *(char *) s2)
		{
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		n--;
		s1++;
		s2++;
	}
	return (0);
}
