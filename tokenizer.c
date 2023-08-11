/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:24:23 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/09 22:44:08 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// here I copy into the t_token directly from input,
// using the same memory
t_token_l	*tokenizer(char **input) {
	t_token_l	*ret;
	t_token		*aux;
	
	aux = NULL;
	// while (*input)
	// {
	// 	aux = malloc(sizeof (t_token));
	// 	if (!aux)
	// 	{
	// 		//free input
	// 		//
	// 	}
	// 	aux->content = *input;
	// 	aux->flag = 
	// }
	if (!aux) 
		return NULL;
	
	aux->content = *input;
	aux->flag = OPERATOR_IN;
	
	ret = NULL;
	ft_lstadd_back((t_list **) &ret, ft_lstnew(aux));
	printf("%s\n", ret->token->content);
	printf("%d\n", ret->token->flag);

	return ret;
}