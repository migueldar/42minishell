/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:59:31 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 20:10:10 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_l	*complete_parser(char *raw, t_env *env)
{
	t_token_l	*tok_list;
	t_command_l	*parsed_list;
	t_command_l	*expanded_list;

	if (raw[0])
		add_history(raw);
	if (is_empty(raw))
	{
		free(raw);
		return (NULL);
	}
	tok_list = lexer(raw);
	free(raw);
	if (!tok_list)
		return (NULL);
	parsed_list = parser_handler(tok_list);
	ft_lstclear((t_list **) &tok_list, (void (*)(void *)) free_token);
	if (!parsed_list)
		return (NULL);
	expanded_list = expander_handler(parsed_list, env);
	ft_lstclear((t_list **) &parsed_list, (void (*)(void *)) free_cmd);
	return (expanded_list);
}
