/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:06:25 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/24 15:46:54 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	char	*ret_cpy;

	ret = ft_calloc(ft_strlen(s1) + 1, 1);
	if (ret == NULL)
		return (ret);
	ret_cpy = ret;
	while (*s1 != 0)
		*(ret++) = *(s1++);
	return (ret_cpy);
}
