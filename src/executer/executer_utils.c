/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 21:16:24 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_childs(int *pid, int position_childs)
{
	int	counter;

	counter = 0;
	while (counter < position_childs)
	{
		kill(pid[counter], SIGKILL);
		counter++;
	}
}

int	wait_all_free(int *pid, int len)
{
	int	counter;
	int	stat;

	counter = 0;
	while (counter < len)
	{
		waitpid(pid[counter], &stat, 0);
		counter++;
	}
	sig_setter(sig_handler_interactive, 1);
	free(pid);
	if (WIFSIGNALED(stat))
		return (WTERMSIG(stat) | 0x80);
	return (WEXITSTATUS(stat));
}

t_command	*isolate_cmd(t_command_l *command_l, int which)
{
	t_command_l	*head_cpy;
	t_command_l	*prev;
	t_command	*ret;

	head_cpy = command_l;
	prev = NULL;
	ret = NULL;
	while (head_cpy)
	{
		if (which == 0)
		{
			if (prev)
				prev->next = head_cpy->next;
			else
				command_l = head_cpy->next;
			ret = head_cpy->cmd;
			free(head_cpy);
			break ;
		}
		prev = head_cpy;
		head_cpy = head_cpy->next;
		which--;
	}
	return (ft_lstclear_cmd_l(&command_l), ret);
}

void	swap_pipes(int pipes[2][2])
{
	int	aux;

	aux = pipes[0][0];
	pipes[0][0] = pipes[1][0];
	pipes[1][0] = aux;
	aux = pipes[0][1];
	pipes[0][1] = pipes[1][1];
	pipes[1][1] = aux;
}

t_child_aux	create_aux_struct(int counter, int in, int out)
{
	t_child_aux	ret;

	ret.counter = counter;
	ret.fdin = in;
	ret.fdout = out;
	return (ret);
}
