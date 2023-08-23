/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:53:22 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/23 04:20:40 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_string_l
{
	char				*content;
	struct s_string_l	*next;
}	t_string_l;

typedef enum e_redir_flag {
	IN,
	HERE_DOC,
	OUT,
	APPEND
}	t_redir_flag;

typedef struct s_redir {
	char			*where;
	t_redir_flag	flag;
}	t_redir;

typedef struct s_redir_l {
	t_redir				*redir;
	struct s_redir_l	*next;
}	t_redir_l;

typedef struct s_command {
	t_string_l	*args;
	t_redir_l	*redirs;
}	t_command;

typedef struct s_command_l {
	t_command			*cmd;
	struct s_command_l	*next;
}	t_command_l;

typedef struct	s_exp_str
{
	char	*content;
	char	*was_expanded;
}	t_exp_str;

typedef struct	s_exp_l
{
	t_exp_str		*content;
	struct	s_exp_l	*next;
}	t_exp_l;

#endif