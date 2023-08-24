/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:23:03 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/24 02:37:08 by mde-arpe         ###   ########.fr       */
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
