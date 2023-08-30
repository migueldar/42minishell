/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:47:51 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/30 02:52:18 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "structs.h"
# include <fcntl.h>

int		resolve_heredocs(t_command_l *commands, t_env *env);
int		executer(t_command_l *cmds, t_env *env);
char	*quote_removal_heredoc(char *str);
char	*temp_name(int *status);
char	*expand_heredoc(char *toexp, t_env *env);
char	*execute_heredoc_settup(char *del, int *fd, char **file_name, int *stat);
void	unlink_all_heredoc(t_command_l *first, t_command_l *last);

#endif