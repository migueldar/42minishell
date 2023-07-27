/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:52:21 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 15:13:59 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*ret_cpy;

	if (!s1 || !s2)
		return (NULL);
	ret = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	ret_cpy = ret;
	if (ret == NULL)
		return (NULL);
	while (*s1 != 0)
		*(ret++) = *(s1++);
	while (*s2 != 0)
		*(ret++) = *(s2++);
	return (ret_cpy);
}
