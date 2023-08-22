/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 02:29:42 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/19 01:08:21 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

//if in_quote != 0, we have unclosed quotes
static size_t	len_next_word(char const *s, char *in_quote)
{
	size_t	counter;

	counter = -1;
	while (s[++counter])
	{
		if (*in_quote && s[counter] == *in_quote)
			*in_quote = 0;
		else if (!*in_quote && (s[counter] == 0x22 || s[counter] == 0x27))
			*in_quote = s[counter];
		else if (!*in_quote && ft_isspace(s[counter]))
			break ;
		else if (!*in_quote && ft_isoperator(s[counter]))
		{
			if (counter != 0)
				break ;
			else if (s[counter] != '|' && s[counter] == s[counter + 1])
				return (2);
			return (1);
		}
	}
	return (counter);
}

static char	*next_word(char const **s, char *status)
{
	size_t	counter;
	size_t	len;
	char	*ret;

	len = len_next_word(*s, status);
	if (*status)
		return (*status = 2, NULL);
	ret = ft_calloc(len + 1, 1);
	if (!ret)
		return (*status = 1, NULL);
	counter = -1;
	while (++counter < len)
		ret[counter] = *((*s)++);
	return (ret);
}

//return NULL means error
//status = 0 empty input
//status = 1 malloc fail
//status = 2 unclosed quotes
t_string_l	*splitter(char const *s, char *status)
{
	t_string_l	*ret;
	t_string_l	*new_n;

	ret = NULL;
	while (*s)
	{
		if (!ft_isspace(*s))
		{			
			new_n = ft_calloc(1, sizeof (t_string_l));
			if (!new_n)
				return (*status = 1, ft_lstclear((t_list **) &ret, free), NULL);
			new_n->content = next_word(&s, status);
			if (!new_n->content)
				return (ft_lstclear((t_list **) &ret, free), free(new_n), NULL);
			ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		}
		else
			s++;
	}
	return (*status = 0, ret);
}
