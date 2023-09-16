/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:47:51 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/16 20:43:52 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "structs.h"
# include <fcntl.h>

int			resolve_heredocs(t_command_l *commands, t_env *env);
int			executer(t_command_l *cmds, t_env **env);
char		*quote_removal_heredoc(char *str);
char		*temp_name(int *status);
char		*expand_heredoc(char *toexp, t_env *env);
char		*execute_heredoc_settup(char *del, int *fd, \
	char **file_nam, int *stat);
void		unlink_all_heredoc_cmd(t_command_l *first, t_command_l *last);
void		unlink_all_heredoc_redir(t_redir_l *first);
t_command	*fork_free_command_l(t_command_l **command_l, int which);
int			single_forked_cmd(t_list *pids);
int			handle_redirs(t_redir_l *redirs);

#endif
