/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:59:31 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/25 19:07:50 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_l	*complete_parser(char *raw, t_env *env)
{
	t_token_l	*tok_list;
	t_command_l	*parsed_list;
	t_command_l	*expanded_list;

	tok_list = lexer(raw);
	free(raw);
	if (!tok_list)
		return (NULL);
	parsed_list = parser_handler(tok_list);
	ft_lstclear((t_list **) &tok_list, (void (*)(void *)) free_token);
	if (!parsed_list)
		return (NULL);
	expanded_list = expander_handler(parsed_list, env);
	command_l_printer(expanded_list);
	ft_lstclear((t_list **) &parsed_list, (void (*)(void *)) free_cmd);
	// ft_lstclear((t_list **) &expanded_list, (void (*)(void *)) free_cmd);
	return (expanded_list);
}
