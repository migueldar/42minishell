/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/15 17:30:28 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*fork_free_command_l(t_command_l **command_l, int which)
{
	int			counter;
	t_command	*fork_command;
	t_command_l	*head;

	counter = 0;
	head = *command_l;
	while (*command_l)
	{
		if (counter == which)
		{
			fork_command = (*command_l)->cmd;
			(*command_l)->cmd = NULL;
		}
		(*command_l) = (*command_l)->next;
		counter ++;
	}
	ft_lstclear_cmd_l(&head);
	return (fork_command);
}


int	single_forked_cmd(t_command_l *cmd)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid > 0)
	{
		//redirecciones
		//verificar comando
		//ejecutar
	}
	else
		wait(NULL);
	return (0);
}

char	**t_env_to_array_bi(t_env *env)
{
	char	**command;
	int		firs_dim;

	command = ft_calloc(sizeof(char *), len_env(env));
	while (env)
	{
		command[firs_dim] = ft_strdup(env->content);
		env = env->next;
		first
	}
}

int	verify_access(t_env *env, t_command *cmd)
{
	char	*unidimensional_path;
	char	**path;
	char	**command;
	int		status;

	unidimensional_path = ft_getenv(env, "PATH", &status);
	if (!unidimensional_path || status == 1)
		return (1);
	path = ft_split(unidimensional_path, ':');
	
}