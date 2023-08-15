/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:15:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/15 21:50:41 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*loop;

	if (!new || !lst)
		return ;
	loop = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (loop->next != NULL)
			loop = loop->next;
		loop->next = new;
	}
}
