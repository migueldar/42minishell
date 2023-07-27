/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:19:34 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/25 01:46:55 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int				minus;
	unsigned int	ret;

	ret = 0;
	minus = 0;
	while (*str == 0x20 || *str == 9 || *str == 10
		|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus++;
		str++;
	}
	while (*str <= '9' && *str >= '0')
		ret = ret * 10 + (*str++ - '0');
	if (ret > 0x7fffffff && !minus)
		return (-1);
	if (ret > 2147483648 && minus)
		return (0);
	if (minus)
		ret *= -1;
	return (ret);
}
