/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:47:51 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 17:05:42 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "structs.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_child_aux
{
	int	counter;
	int	fdin;
	int	fdout;
}	t_child_aux;

int			resolve_heredocs(t_command_l *commands, t_env *env);
int			executer(t_command_l *cmds, t_env **env);
char		*quote_removal_heredoc(char *str);
char		*temp_name(int *status);
char		*expand_heredoc(char *toexp, t_env *env);
char		*execute_heredoc_settup(char *del, int *fd, \
	char **file_nam, int *stat);
void		unlink_all_heredoc_cmd(t_command_l *first, t_command_l *last);
void		unlink_all_heredoc_redir(t_redir_l *first);
int			handle_redirs(t_redir_l *redirs);
int			single_cmd(t_env **env, t_command_l *cmd);
char		*find_path(t_env *env, char *cmd, int *status);
int			handle_dups(int fdin, int fdout);
int			plural_commands(t_env **env, t_command_l *cmd);
void		childs_tasks(t_env **env, t_command *cmd);
t_command	*isolate_cmd(t_command_l *command_l, int which);
void		clear_child(t_env **env, t_command *cmd, char *arg1, char **arg2);
int			handle_builtin(t_command *cmd, t_env **env, int single);
void		swap_pipes(int pipes[2][2]);
t_child_aux	create_aux_struct(int counter, int in, int out);
void		kill_childs(int *pid, int position_childs);
int			wait_all_free(int *pid, int len);

#endif
