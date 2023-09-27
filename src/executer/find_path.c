/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:32:37 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/27 20:05:05 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_if_slash(char *cmd)
{
	int			counter;
	struct stat	st;

	counter = 0;
	while (cmd[counter] && cmd[counter] != '/')
		counter ++;
	if (cmd[counter] == 0)
		return (0);
	if (stat(cmd, &st) == -1)
		return (1);
	else
	{
		if (S_ISDIR(st.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": is a directory\n", 17);
			return (2);
		}
		if (access(cmd, X_OK) == -1)
			return (perror("minishell"), 2);
	}
	return (1);
}

static char	*ft_strjoinpath(char const *s1, char const *s2)
{
	char	*s;
	int		l;

	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = malloc((l + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (*s1)
		*s++ = *s1++;
	*s++ = '/';
	while (*s2)
		*s++ = *s2++;
	*s = 0;
	return (s - l);
}

// status 1 if path not found or empty path
static char	**create_path(t_env *env, int *status)
{
	char	*unidim_path;
	char	**paths;

	*status = 0;
	unidim_path = ft_getenv(env, "PATH", status);
	if (!unidim_path)
		return (NULL);
	if (unidim_path[0] == 0)
		return (free(unidim_path), *status = 1, NULL);
	paths = ft_split(unidim_path, ':');
	free(unidim_path);
	return (paths);
}

static char	*verify_path(char **paths, char	*cmd, int *status)
{
	int		counter;
	char	*complete_path;

	counter = 0;
	*status = 0;
	while (paths[counter])
	{
		complete_path = ft_strjoinpath(paths[counter], cmd);
		if (!complete_path)
			return (NULL);
		if (access(complete_path, X_OK) != -1)
			return (complete_path);
		else
			errno = 0;
		counter++;
		free(complete_path);
	}
	return (*status = 1, NULL);
}

char	*find_path(t_env *env, char *cmd, int *stat)
{
	char	**paths;
	char	*correct_path;
	int		status;

	if (verify_if_slash(cmd) == 2)
		return (*stat = 126, NULL);
	else if (verify_if_slash(cmd) == 1)
		return (ft_strdup_perror(cmd));
	paths = create_path(env, &status);
	if (!paths)
	{
		if (status == 0)
			return (perror("minishell"), NULL);
		return (ft_strdup_perror(cmd));
	}
	correct_path = verify_path(paths, cmd, &status);
	free_arr_2((void **) paths);
	if (!correct_path)
	{
		if (status == 0)
			return (perror("minishell"), NULL);
		write((write(2, "minishell: ", 11), 2), cmd, ft_strlen(cmd));
		return (*stat = 127, write(2, ": command not found\n", 20), NULL);
	}
	return (correct_path);
}
