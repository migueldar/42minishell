/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:25:53 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/12 21:42:53 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// cuando finalice el splitter, hacer comprobacion de todos los mallocs
t_token_l	*lexer(char *raw_input) {
	//t_token_l	*ret;
	t_string_l	*split_raw_input;
	char		status;
	
	split_raw_input = splitter(raw_input, &status);
	if (!split_raw_input)
	{
		if (status == 1)
			write(2, "Malloc failed\n", 15);
		else if (status == 2)
			write(2, "Syntax error: unclosed quotes\n", 31);
		return NULL;
	}
	//free_arr_2((void **) split_raw_input);
	int i = -1;
	while (split_raw_input)
	{
		printf("Param %d: %s\n", ++i, split_raw_input->content);
		split_raw_input = split_raw_input->next;
	}
	// ret = tokenizer(split_raw_input);
	// if (!ret) // liberar splitter
	// 	write(2, "Malloc failed\n", 15);
	
	return NULL;
}
