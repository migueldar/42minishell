/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:14:24 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/11 01:29:35 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//having to create a trash pointer just to del it feels so bad
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*aux;
	void	*new;

	if (!lst)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		new = (*f)(lst->content);
		aux = ft_lstnew(new);
		if (!aux)
		{
			del(new);
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, aux);
		lst = lst->next;
	}
	return (ret);
}
