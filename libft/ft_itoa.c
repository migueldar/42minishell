/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:53:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/25 02:48:44 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_of_int(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*ret;
	char	*ret_cpy;
	long	long_n;
	int		div;

	ret = ft_calloc(size_of_int(n) + 1, 1);
	if (ret == NULL)
		return (NULL);
	ret_cpy = ret;
	long_n = n;
	div = 1;
	if (long_n < 0)
	{
		*ret = '-';
		ret++;
		long_n *= -1;
	}
	while (long_n / div > 9)
		div *= 10;
	while (div)
	{
		*(ret++) = '0' + (long_n / div) % 10;
		div /= 10;
	}
	return (ret_cpy);
}
