/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:53:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/21 22:20:13 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>

// // add history should not add empty lines
// int main()
// {
// 	char		*raw;
// 	t_token_l	*tok_list;
// 	t_command_l	*parsed_list;
// 	// t_command_l *expanded_list;
	
// 	#ifdef MALLOC_DEBUG
// 	atexit(leaks);
// 	#endif

// 	g_exit_status = ST_OK;
// 	sig_setter(sig_handler_interactive);
// 	while (1)
// 	{
// 		raw = readline("$> ");
// 		if (!raw)   // ctrl + D
// 			break ; // will have to free all
// 		// printf("%s\n", raw);
// 		add_history(raw);
// 		tok_list = lexer(raw);
// 		free(raw);
// 		if (!tok_list)
// 			continue ;
// 		parsed_list = parser_handler(tok_list);
// 		// command_l_printer(parsed_list);
// 		ft_lstclear((t_list **) &tok_list, (void (*)(void *)) free_token);
// 		if (!parsed_list)
// 			continue ;
// 		ft_lstclear((t_list **) &parsed_list, (void (*)(void *)) free_cmd);
// 	}
// 	clear_history();
// }
