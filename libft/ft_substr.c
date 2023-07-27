/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:51:54 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/25 00:34:25 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		ret = ft_calloc(1, 1);
		return (ret);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	ret = ft_calloc((len + 1), 1);
	if (ret == NULL)
		return (NULL);
	if (ft_strlen(s) > (size_t) start)
		ft_strlcpy(ret, (char *)(s + start), len + 1);
	return (ret);
}
