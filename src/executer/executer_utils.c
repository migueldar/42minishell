/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/16 21:51:06 by lucia-ma         ###   ########.fr       */
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

static char	*ft_strjoinpath(char const *s1, char const *s2)
{
	char	*s;
	int		l;

	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = malloc(l * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	while (*s1)
		*s++ = *s1++;
	*s++ = 47;
	while (*s2)
		*s++ = *s2++;
	*s = 0;
	return (s - l);
}

int	single_forked_cmd()
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
static int	verify_if_slash(char *cmd)
{
	int	counter;

	counter = 0;
	while (cmd[counter] && cmd[counter] != '/')
		counter ++;
	if (cmd[counter])
		return (1);
	return (0);
}

char	*find_path(t_env *env, char *cmd)
{
	int		counter;
	char	*complete_path;
	char	**paths;
	int		status;	
	char	*unidim_path;

	if (verify_if_slash(cmd))
		return (cmd);
	counter = 0;
	unidim_path = ft_getenv(env, "PATH", &status);
	if (status == 1)
		return (cmd);
	paths = ft_split(unidim_path, ':');
	while (paths[counter])
	{
		complete_path = ft_strjoinpath(paths[counter], cmd);
		if (!complete_path)
			return (perror("minishell"), NULL);
		if (access(complete_path, X_OK) != -1)
			return (complete_path);
		counter ++;
	}
	return (cmd);
}
