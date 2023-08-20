/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:21:48 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/20 16:38:15 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins.h"

int	ft_clear_envlist(t_env **env)
{
	t_env	*next;
	t_env	*head;

	if (!*env)
		return (1);
	head = *env;
	while (head)
	{
		next = head->next;
		free(head->content->key);
		printf("entras %s\n", head->content->value);
		free(head->content->value);
		free(head);
		head = next;
	}
	*env = NULL;
	return(0);
}

char	*get_pwd(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PWD=", 4) == 0)
			break ;
		env ++;
	}
	if (*env)
		return (*env + 4);
	return (NULL);
}
