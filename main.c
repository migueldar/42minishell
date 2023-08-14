/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:53:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/15 00:18:16 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add history should not add empty lines
int main()
{
	char		*raw;
	t_token_l	*tok_list;
	t_command_l	*parsed_list;
	// t_command_l *expanded_list;
	
	#ifdef MALLOC_DEBUG
	atexit(leaks);
	#endif

	for (int i = 0; i<1; i++)
	{
		raw = readline("$> ");
		add_history(raw);
		tok_list = lexer(raw);
		free(raw);
		if (!tok_list)
			continue ;
		parsed_list = parser_handler(tok_list);
		ft_lstclear((t_list **) &tok_list, (void (*)(void *)) free_token);
		if (!parsed_list)
			continue ;
		ft_lstclear((t_list **) &parsed_list, (void (*)(void *)) free_cmd);
	}
	clear_history();
}
