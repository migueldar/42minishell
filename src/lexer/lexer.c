/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:25:53 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/21 22:26:10 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// returns NULL if any of these happen:
// - malloc fail
// - unclosed quotes
// - empty input
t_token_l	*lexer(char *raw_input)
{
	t_string_l	*split_raw_input;
	t_token_l	*ret;
	char		status;

	split_raw_input = splitter(raw_input, &status);
	if (!split_raw_input)
	{
		if (status == 1)
			write(2, "Malloc failed\n", 15);
		else if (status == 2)
			write(2, "Syntax error: unclosed quotes\n", 31);
		return (NULL);
	}
	ret = tokenizer(split_raw_input);
	ft_lstclear((t_list **) &split_raw_input, free);
	if (!ret)
	{
		write(2, "Malloc failed\n", 15);
		return (NULL);
	}
	return (ret);
}
