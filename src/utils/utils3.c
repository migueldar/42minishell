/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:23:03 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/08 21:06:56 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//joins two list but the last content of head and 
//the first content of add get joined in just one node
//returns 0 if all ok, 1 if malloc fails
int	lst_addback_append(t_string_l **head, t_string_l *add)
{
	t_string_l	*head_cpy;
	t_string_l	*add_cpy;
	char		*aux;

	if (!(*head))
	{
		*head = add;
		return (0);
	}
	if (!add)
		return (0);
	head_cpy = *head;
	while (head_cpy->next != NULL)
		head_cpy = head_cpy->next;
	aux = protected_strjoin(head_cpy->content, add->content);
	if (!aux)
		return (1);
	free(head_cpy->content);
	free(add->content);
	add_cpy = add;
	add = add->next;
	free(add_cpy);
	head_cpy->content = aux;
	head_cpy->next = add;
	return (0);
}

void	lst_delnode(t_list **head, t_list *node, void (*del)(void *))
{
	t_list	*head_cpy;
	t_list	*prev;
	
	if (!head || !*head || !node || !del)
		return ;
	head_cpy = *head;
	prev = NULL;
	while (head_cpy)
	{
		if (head_cpy == node)
		{
			if (prev)
				prev->next = head_cpy->next;
			else
				*head = head_cpy->next;
			ft_lstdelone(head_cpy, del);
			break ;
		}
		prev = head_cpy;
		head_cpy = head_cpy->next;
	}
}

// returns a string of size n full of char c
char	*full_string(char c, size_t n)
{
	char	*ret;

	ret = ft_calloc(n + 1, 1);
	if (!ret)
		return (NULL);
	while (n-- > 0)
		ret[n] = c;
	return (ret);
}
