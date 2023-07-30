/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:24:23 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/07/30 21:40:06 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_l	*tokenizer(char **input) {
	t_token_l	*ret;
	t_token		*aux;
	
	while (*input)
		aux = malloc(sizeof (t_token));
	if (!aux) 
		return NULL;
	
	aux->content = *input;
	aux->flag = OPERATOR;
	
	ret = NULL;
	ft_lstadd_back((t_list **) &ret, ft_lstnew(aux));
	printf("%s\n", ret->token->content);
	printf("%d\n", ret->token->flag);

	return ret;
}