/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:00:38 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/23 02:08:42 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	uc;
	size_t			counter;
	unsigned char	*point;

	point = (unsigned char *) b;
	counter = 0;
	uc = c;
	while (counter < len)
	{
		*point = uc;
		counter++;
		point++;
	}
	return (b);
}
