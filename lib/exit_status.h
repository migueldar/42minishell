/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 01:43:00 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/18 18:09:41 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# define ST_OK				0
# define ST_SIGINT			1
# define ST_AMB_REDIR		1
# define ST_SIGQUIT			131
# define ST_NON_NUM_EXIT	255
# define ST_SYNTAX_ERROR	258
# define ST_SIGINT_HEREDOC	1025
# define ST_EXIT			2048

#endif
