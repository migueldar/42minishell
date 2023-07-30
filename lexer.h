/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 04:26:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/07/27 17:09:34 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "libft/libft.h"

typedef struct s_token {
	char	*content;
	int		flags;
}	t_token;

typedef struct s_token_l
{
	t_token				token;
	struct s_token_l	*next;
}	t_token_l;

t_token_l	*lexer(char *raw_input);

#endif