/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 00:58:38 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/26 17:04:09 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_setter(sig_t func)
{
	signal(SIGINT, func);
	signal(SIGQUIT, func);
}

void	sig_handler_wait(int signum)
{
	(void) signum;
	write(1, "\n", 1);
}

void	sig_handler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = ST_SIGINT;
	}
}

void	sig_handler_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		g_exit_status = ST_SIGINT_HEREDOC;
	}
}
