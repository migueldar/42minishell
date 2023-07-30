/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:25:53 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/07/30 21:39:15 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_token_l	*lexer(char *raw_input) {
	t_token_l	*ret;
	char		**split_raw_input;
	//int i = -1;
	
	split_raw_input = word_split(raw_input);
	if (!split_raw_input)
		write(2, "Malloc failed\n", 15);
	// while (split_raw_input && split_raw_input[++i])
	// 	printf("Param %d: %s\n", i, split_raw_input[i]);
	ret = tokenizer(split_raw_input);
	if (!ret)
		write(2, "Malloc failed\n", 15);
	
	return ret;
}