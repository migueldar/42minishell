/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:32:37 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/28 20:32:00 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_errors(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == -1)
		return (1);
	if (S_ISDIR(st.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		return (write(2, ": is a directory\n", 17), 2);
	}
	if (access(cmd, X_OK) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		return (write(2, ": Permission denied\n", 20), 2);
	}
	return (1);
}

static int	verify_slash_path(char *cmd, t_env *env)
{
	int			counter;
	int			status;
	char		*path;

	status = 0;
	path = ft_getenv(env, "PATH", &status);
	if (!path && status == 0)
		return (perror("minishell"), 3);
	if (!path)
		return (verify_errors(cmd));
	free(path);
	counter = 0;
	while (cmd[counter] && cmd[counter] != '/')
		counter++;
	if (cmd[counter] == 0)
		return (0);
	return (verify_errors(cmd));
}

static char	**create_path(t_env *env)
{
	char	*unidim_path;
	char	**paths;
	int		status;

	unidim_path = ft_getenv(env, "PATH", &status);
	if (!unidim_path)
		return (NULL);
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
	int		verify;

	verify = verify_slash_path(cmd, env);
	if (verify == 1)
		return (ft_strdup_perror(cmd));
	else if (verify == 2)
		return (*stat = 126, NULL);
	else if (verify == 3)
		return (*stat = 1, NULL);
	paths = create_path(env);
	if (!paths)
		return (perror("minishell"), NULL);
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
