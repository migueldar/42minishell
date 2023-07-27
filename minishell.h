/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 03:48:31 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/07/27 04:58:38 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_redir_flag {
	IN,
	OUT,
	OUTAPPEND,
	HERE_DOC
}	t_redir_flag;

typedef struct s_redir {
	char			*where;
	t_redir_flag	type;
}	t_redir;

typedef struct s_command {
	char	**args;
	t_redir	*redirections;
}	t_command;

// this is the list that the executer will recieve (beta)
typedef struct s_command_list {
	t_command				cmd;
	struct s_command_list	*next;
}	t_command_list;

#endif