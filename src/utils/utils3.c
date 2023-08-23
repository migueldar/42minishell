/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:23:03 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/23 04:19:24 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*next_word(t_exp_str exp, size_t *counter)
// {
// 	size_t	len;
// 	char	*ret;

// 	len = 0;
// 	while ((exp.content)[counter + len] && !ft_isspace((*s)[len]))
// 		len++;
// 	ret = ft_calloc(len + 1, 1);
// 	if (!ret)
// 		return ( NULL);
// 	counter = -1;
// 	while (++counter < len)
// 		ret[counter] = *((*s)++);
// 	return (ret);
// }

// t_exp_l	*split_to_list(t_exp_str exp)
// {
// 	t_exp_l		*ret;
// 	t_string_l	*new_n;
// 	size_t		counter;
// 	char		in_quote;

// 	ret = NULL;
// 	counter = 0;
// 	in_quote = 0;
// 	while ((exp.content)[counter])
// 	{
// 		if (in_quote && (exp.content)[counter] == in_quote)
// 			in_quote = 0;
// 		else if (!in_quote && ((exp.content)[counter] == 0x22 || (exp.content)[counter] == 0x27))
// 			in_quote = (exp.content)[counter];
// 		if (!ft_isspace(exp.content[counter]) && )
// 		{			
// 			new_n = ft_calloc(1, sizeof (t_exp_l));
// 			if (!new_n)
// 				return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_env_var), NULL);
// 			new_n->content = next_word(&(exp.content));
// 			if (!new_n->content)
// 				return (ft_lstclear((t_list **) &ret, (void (*)(void *)) free_env_var), free(new_n), NULL);
// 			ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
// 		}
// 		else
// 			counter++;
// 	}
// 	return (ret);
// }

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
