/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:23:03 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 16:57:32 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_strncmp_ignore_case(const char *s1, const char *s2, unsigned int n)
{
	while ((*s1 || *s2) && n > 0)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*ft_strdup_perror(char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	if (!ret)
		perror("minishell");
	return (ret);
}
