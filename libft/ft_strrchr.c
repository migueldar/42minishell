/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:02:48 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/23 02:11:24 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char		find;
	const char	*initial_position;

	initial_position = s;
	find = c;
	while (*s)
		s++;
	while (*s != find)
	{
		if (s == initial_position)
			return (0);
		s--;
	}
	return ((char *) s);
}
