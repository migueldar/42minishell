/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:15:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/03/23 17:48:44 by mde-arpe         ###   ########.fr       */
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
