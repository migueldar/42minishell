/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:54:18 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 15:21:04 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		counter;

	if (!s)
		return (NULL);
	counter = 0;
	ret = ft_calloc(ft_strlen(s) + 1, 1);
	if (ret == NULL)
		return (NULL);
	while (s[counter])
	{
		ret[counter] = (*f)(counter, s[counter]);
		counter++;
	}
	return (ret);
}
