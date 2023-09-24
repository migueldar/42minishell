/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:25:53 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/18 21:08:03 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns NULL if any of these happen:
// - malloc fail
// - unclosed quotes
// - empty input
t_token_l	*lexer(char *raw_input)
{
	t_string_l	*split_raw_input;
	t_token_l	*ret;
	char		status;

	status = 0;
	split_raw_input = splitter(raw_input, &status);
	if (!split_raw_input)
	{
		if (status == 1)
			perror("minishell");
		else if (status == 2)
			write(2, "minishell: syntax error: unclosed quotes\n", 41);
		return (g_exit_status = 1, NULL);
	}
	ret = tokenizer(split_raw_input);
	ft_lstclear((t_list **) &split_raw_input, free);
	if (!ret)
	{
		perror("minishell");
		return (g_exit_status = 1, NULL);
	}
	return (ret);
}
