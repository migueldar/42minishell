/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/29 03:39:13 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer(t_command_l *cmds, t_env *env)
{
	resolve_heredocs(cmds, env);
	command_l_printer(cmds);
}