/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:26:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/17 02:57:43 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "libft/libft.h"
# include "utils.h"

typedef enum e_token_flag {
	OP_IN,
	OP_HERE_DOC,
	OP_OUT,
	OP_APPEND,
	OP_PIPE,
	WORD
}	t_token_flag;

typedef struct s_token {
	char			*content;
	t_token_flag	flag;
}	t_token;

typedef struct s_token_l
{
	t_token				*token;
	struct s_token_l	*next;
}	t_token_l;

t_token_l	*lexer(char *raw_input);
t_token_l	*tokenizer(t_string_l *input);
t_string_l	*splitter(char const *s, char *status);
void		free_token(t_token *token);

#endif