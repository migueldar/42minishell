/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:46:09 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/22 20:54:13 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "command.h"
# include "builtins.h"
# include <stdlib.h>
# include "libft.h"
# include "utils.h"

t_command_l	*expander(t_command_l *cmds, t_env *env);

#endif