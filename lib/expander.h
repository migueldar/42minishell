/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:46:09 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/24 04:21:04 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"
# include "builtins.h"
# include <stdlib.h>
# include "libft.h"
# include "utils.h"

t_command_l	*expander(t_command_l *cmds, t_env *env);
t_exp_l		*word_split(t_exp_str exp);
t_string_l	*quote_removal(t_exp_l *exp_l);
t_exp_str	expand_argument(char *str, t_env *env, int *status);

#endif