/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:10:47 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/24 22:01:14 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_removal_heredoc(char *str)
{
	char	*ret;
	char	*aux;
	char	in_quote;

	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	in_quote = 0;
	while (str && *str)
	{
		if (!in_quote && (*str == 0x22 || *str == 0x27))
			in_quote = *str;
		else if (in_quote && *str == in_quote)
			in_quote = 0;
		else
		{
			aux = protected_strcharjoin(ret, *str);
			free(ret);
			if (!aux)
				return (NULL);
			ret = aux;
		}
		str++;
	}
	return (ret);
}

char	*temp_name(int *status)
{
	int		i;
	char	*itoaed;
	char	*name;

	i = -1;
	while (++i <= 0x7fffffff)
	{
		itoaed = ft_itoa(i);
		if (!itoaed)
			return (NULL);
		name = ft_strjoin("/tmp/minish-thd-", itoaed);
		free(itoaed);
		if (!name)
			return (NULL);
		if (access(name, F_OK) == -1)
			return (errno = 0, name);
		free(name);
	}
	return (*status = 3, NULL);
}

char	*expand_heredoc(char *toexp, t_env *env)
{
	char	*ret;
	char	*aux;
	char	*aux2;
	int		status;

	ret = ft_strdup("");
	while (*toexp)
	{
		if (*toexp == '$')
		{
			toexp++;
			aux2 = expand_substring(&toexp, env, 1, &status);
			if (toexp--, !aux2 && !status)
				return (free(ret), NULL);
			aux = protected_strjoin(ret, aux2);
			free(aux2);
		}
		else
			aux = protected_strcharjoin(ret, *toexp);
		if (free(ret), !aux)
			return (NULL);
		ret = (toexp++, aux);
	}
	return (ret);
}

//returns exp_del
char	*execute_heredoc_settup(char *del, int *fd, char **file_nam, int *stat)
{
	char	*exp_del;

	*file_nam = temp_name(stat);
	if (!*file_nam)
		return (NULL);
	*fd = open(*file_nam, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (*fd == -1)
		return (*stat = 2, free(*file_nam), NULL);
	exp_del = quote_removal_heredoc(del);
	if (!exp_del)
		return (unlink(*file_nam), free(*file_nam), NULL);
	return (exp_del);
}
