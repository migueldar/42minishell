/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:47:51 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/29 03:39:22 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "structs.h"
# include <fcntl.h>

int		resolve_heredocs(t_command_l *commands, t_env *env);
void	executer(t_command_l *cmds, t_env *env);

#endif