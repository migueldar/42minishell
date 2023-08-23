/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:36:40 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/23 04:21:10 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <stdio.h>
# include "utils.h"
# include "structs.h"
# include "builtins.h"

t_command_l	*parser_handler(t_token_l *toks);
void		free_cmd(t_command *cmd);
void		free_redir(t_redir *redir);
void		free_cmd(t_command *cmd);
char		add_redir(t_command *cmd, t_token *redir, t_token *word);
char		add_word(t_command *cmd, t_token *token);
t_command_l	*complete_parser(char *raw, t_env *env);

#endif