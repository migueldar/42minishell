/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:57:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 04:03:32 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;
	int		div;
	char	c;	

	long_n = n;
	div = 1;
	if (long_n < 0)
	{
		write(fd, "-", 1);
		long_n *= -1;
	}
	while (long_n / div > 9)
		div *= 10;
	while (div)
	{
		c = '0' + (long_n / div) % 10;
		write(fd, &c, 1);
		div /= 10;
	}
}
