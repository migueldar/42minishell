/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 00:58:38 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/21 22:16:34 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_setter(sig_t func)
{
	signal(SIGINT, func);
	signal(SIGQUIT, SIG_IGN);
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
		write(1, "\n", 1);
		//g_exit_status = ST_SIGINT;
	}
}
