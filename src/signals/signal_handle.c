/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 00:58:38 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 21:13:41 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_setter(sig_t func, int flag)
{
	signal(SIGINT, func);
	if (flag == 0)
		signal(SIGQUIT, func);
	else
		signal(SIGQUIT, SIG_IGN);
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
