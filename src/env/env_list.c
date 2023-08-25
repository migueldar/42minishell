/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/26 00:16:22 by lucia-ma         ###   ########.fr       */
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
	while (iterator --)
	{
		str[0][counter] = **content;
		counter ++;
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
		length ++;
	env_var->key = ft_calloc(sizeof(char), length + 1);
	if (!env_var->key)
		return (free_env_var(env_var), NULL);
	put_content(length, &env_var->key, &env);
	length = ft_strlen(env);
	env_var->value = ft_calloc(sizeof(char), length);
	if (!env_var->value)
		return (free_env_var(env_var), NULL);
	env++;
	put_content(length, &env_var->value, &env);
	return (env_var);
}

int	ft_noenv(t_env **envi)
{
	int		counter;
	t_env	*new;

	counter = 3;
	while (counter --)
	{
		new = ft_calloc(1, sizeof (t_env));
		if (!new)
		{
			write(2, "malloc env fail in env\n", 24);
			ft_lstclear((t_list **) envi, (void (*)(void *)) free_env_var);
			return (1);
		}
		ft_lstadd_back((t_list **)envi, (t_list *)new);
	}
	(*envi)->content = ft_calloc(1, sizeof(t_env_var));
	(*envi)->content->key = "PWD";
	(*envi)->content->value = getcwd(NULL, 0);
	if (!(*envi)->content->value)
	{
		ft_lstclear((t_list **) &envi, (void (*)(void *)) free_env_var);
		return (1);
	}
	(*envi)->next->content = ft_calloc(1, sizeof(t_env_var));
	(*envi)->next->content->key = "SHLVL";
	(*envi)->next->content->value = "1";
	(*envi)->next->next->content = ft_calloc(1, sizeof(t_env_var));
	(*envi)->next->next->content->key = "_";
	(*envi)->next->next->content->value = "/usr/bin/env";

	return (0);
}

// handle empty env, shouldnt return NULL
t_env	*create_env_list(char **env)
{
	t_env	*envi;
	t_env	*new;
	int		counter;
	int		value;


	counter = -1;
	envi = NULL;
	if (!*env)
	{
		value = ft_noenv(&envi);
		if (value == 1)
			return (NULL);
		ft_print_env(envi);
		return (envi);
	}
	while (env[++counter])
	{
		new = ft_calloc(1, sizeof (t_env));
		if (!new)
		{
			write(2, "malloc env fail in env\n", 24);
			ft_lstclear((t_list **) &envi, (void (*)(void *)) free_env_var);
			return (NULL);
		}
		new->content = create_env_var(env[counter]);
		if (!new->content)
		{
			write(2, "malloc env fail in env\n", 24);
			ft_lstclear((t_list **) &envi, (void (*)(void *)) free_env_var);
			return (free(new), NULL);
		}
		ft_lstadd_back((t_list **)&envi, (t_list *)new);
	}
	return (envi);
}
