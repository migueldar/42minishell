/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/08 19:24:53 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_env_var(t_env_var *env_var)
{
	if (!env_var)
		return ;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	put_content(int iterator, char **str, char **content)
{
	int	counter;

	counter = 0;
	while (iterator--)
	{
		str[0][counter] = **content;
		counter++;
		(*content)++;
	}
}

t_env_var	*create_env_var(char *env)
{
	t_env_var		*env_var;
	int				length;

	length = 0;
	env_var = ft_calloc(1, sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	while (env[length] && env[length] != '=')
		length++;
	env_var->key = ft_calloc(sizeof(char), length + 1);
	if (!env_var->key)
		return (free_env_var(env_var), NULL);
	put_content(length, &env_var->key, &env);
	env++;
	length = ft_strlen(env);
	env_var->value = ft_calloc(sizeof(char), length + 1);
	if (!env_var->value)
		return (free_env_var(env_var), NULL);
	put_content(length, &env_var->value, &env);
	return (env_var);
}

// handle empty env, shouldnt return NULL
t_env	*create_env_list(char **env)
{
	t_env	*ret;
	t_env	*new;
	int		counter;

	counter = -1;
	ret = NULL;
	while (env[++counter])
	{
		new = ft_calloc(1, sizeof (t_env));
		if (!new)
		{
			perror("minishell");
			ft_lstclear((t_list **) &ret, (void (*)(void *)) free_env_var);
			return (NULL);
		}
		new->content = create_env_var(env[counter]);
		if (!new->content)
		{
			perror("minishell");
			ft_lstclear((t_list **) &ret, (void (*)(void *)) free_env_var);
			return (free(new), NULL);
		}
		ft_lstadd_back((t_list **)&ret, (t_list *)new);
	}
	return (ret);
}
