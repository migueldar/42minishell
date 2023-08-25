/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:46:09 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/25 05:54:40 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"
# include "builtins.h"
# include <stdlib.h>
# include "libft.h"
# include "utils.h"

t_command_l	*expander(t_command_l *cmds, t_env *env, int *status);
t_exp_l		*word_split(t_exp_str exp);
t_string_l	*quote_removal(t_exp_l *exp_l);
t_exp_str	expand_argument(char *str, t_env *env, int *status);
void		free_exp_str(t_exp_str to_free);
char		in_quote_switch(char in_quote, char curr);
t_exp_str	protected_exp_join(t_exp_str exp, char *cont,
				char *was_e, int is_str);
void		init_to_zeros(char *str, t_exp_str *exp);
int			in_quote_switch2(char *in_q, t_exp_str *exp, int cnt);
t_exp_str	*next_word_ex(t_exp_str exp, size_t *cnt, char *in_quote);
void		ft_lstclear_cmd_l(t_command_l **tofree);
t_command_l	*expander_handler(t_command_l *cmds, t_env *env);
void		ft_lstclear_exp_l(t_exp_l **tofree);

#endif