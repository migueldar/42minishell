/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:54:42 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 15:38:46 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		counter;

	if (!f || !s)
		return ;
	counter = 0;
	while (s[counter])
	{
		(*f)(counter, &s[counter]);
		counter++;
	}
}
