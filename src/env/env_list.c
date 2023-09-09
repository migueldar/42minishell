/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/08 16:56:06 by lucia-ma         ###   ########.fr       */
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
		return (perror(""), NULL);


	while (env[length] && env[length] != '=')
		length ++;
	env_var->key = ft_calloc(sizeof(char), length + 1);
	if (!env_var->key)
		return (perror(""), free_env_var(env_var), NULL);
	if(!env[length])
	{
		put_content(length, &env_var->key, &env);
		return(env_var);
	}
	put_content(length, &env_var->key, &env);
	if (!env)
	{
		return(env_var);
	}
	length = ft_strlen(env);
	env_var->value = ft_calloc(sizeof(char), length);
	if (!env_var->value)
		return (perror(""), free_env_var(env_var), NULL);
	env++;
	
	put_content(length, &env_var->value, &env);
	return (env_var);
}

t_env	*ft_noenv(t_env *envi)
{
	t_env	*new;

	new = ft_calloc(1, sizeof (t_env));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	ft_lstadd_back((t_list **)&envi, (t_list *)new);
	envi->content = ft_calloc(1, sizeof(t_env_var));
	if (envi->content == NULL)
		return (NULL);
	envi->next->content->key = ft_strdup("SHLVL");
	if (envi->next->content->key == NULL)
		return (NULL);
	envi->next->content->value = ft_strdup("1");
	if (envi->next->content->value == NULL)
		return (NULL);
	return (envi);
}

void	ft_env_return_error(t_env	*envi, char *message)
{
	while (message)
	{
		write(2, message, 1);
		message ++;
	}
	ft_lstclear((t_list **) &envi, (void (*)(void *)) free_env_var);
}

// handle empty env, shouldnt return NULL
t_env	*create_env_list(char **env)
{
	t_env	*envi;
	t_env	*new;
	int		counter;

	envi = ((counter = -1), NULL);
	if (!*env)
	{
		if (ft_noenv(envi) == NULL)
			return (write(2, "malloc env fail in env NO_ENV\n", 24), NULL);
		return (envi);
	}
	while (env[++counter])
	{
		new = ft_calloc(1, sizeof (t_env));
		if (!new)
		{
			write(2, "malloc env fail in env 1\n", 24);
			ft_lstclear((t_list **) &envi, (void (*)(void *)) free_env_var);
			return (NULL);
		}
		new->content = create_env_var(env[counter]);
		if (!new->content)
		{
			write(2, "malloc env fail in env 2\n", 24);
			ft_lstclear((t_list **) &envi, (void (*)(void *)) free_env_var);
			return (free(new), NULL);
		}
		ft_lstadd_back((t_list **)&envi, (t_list *)new);
	}
	return (envi);
}
