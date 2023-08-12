/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:26:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/12 18:52:46 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "libft/libft.h"

typedef enum e_token_flag {
	OPERATOR_IN,
	OPERATOR_HERE_DOC,
	OPERATOR_OUT,
	OPERATOR_APPEND,
	OPERATOR_PIPE,
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

typedef struct s_string_l
{
	char				*content;
	struct s_string_l	*next;
}	t_string_l;

t_token_l	*lexer(char *raw_input);
t_token_l	*tokenizer(char **input);
t_string_l	*splitter(char const *s, char *status);

#endif