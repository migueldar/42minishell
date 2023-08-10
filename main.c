/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:53:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/09 22:55:45 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

//probably need to free output from readline
int main()
{
	char	*raw;
	t_token_l *tok_list;
	
	while (1) {
		raw = readline("$> ");
		tok_list = lexer(raw);
	}
}
