/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:25:53 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/10 00:42:16 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// cuando finalice el splitter, hacer comprobacion de todos los mallocs
t_token_l	*lexer(char *raw_input) {
	t_token_l	*ret;
	char		**split_raw_input;
	char		status;
	
	status = 0;
	split_raw_input = splitter(raw_input, &status);
	if (!split_raw_input)
	{
		if (status == 0)
			write(2, "Malloc failed\n", 15);
		else if (status == 1)
			write(2, "Syntax error: unclosed quotes\n", 31);
		else if (status == 2)
			write(2, "Syntax error: unexpected token\n", 32);
		return NULL;
	}

	int i = -1;
	while (split_raw_input && split_raw_input[++i])
		printf("Param %d: %s\n", i, split_raw_input[i]);
	ret = tokenizer(split_raw_input);
	// if (!ret) // liberar splitter
	// 	write(2, "Malloc failed\n", 15);
	
	return ret;
}
