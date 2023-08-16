/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/16 12:12:05 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	ft_free_env_value(void *env_value)
{
	t_env_var	*k_v_to_free;

	k_v_to_free = env_value;
	free(k_v_to_free->key);
	free(k_v_to_free->value);
	free(k_v_to_free);
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

t_env_var	*create_env_value(char *env)
{
	t_env_var		*env_value;
	int				length;

	length = 0;
	env_value = ft_calloc(sizeof(t_env_var *), 1);
	while (env[length] && env[length] != '=')
		length ++;
	env_value->key = ft_calloc(sizeof(char), length + 1);
	if (env_value->key == NULL)
		return (NULL);
	put_content(length, &env_value->key, &env);
	length = ft_strlen(env);
	env_value->value = ft_calloc(length, sizeof(char));
	if (env_value->value == NULL)
		return (NULL);
	env ++;
	put_content(length, &env_value->value, &env);
	return (env_value);
}

int	free_env_l(t_env **envi)
{
	ft_lstclear((t_list **) &envi, (void *)ft_free_env_value);
	write(2, "malloc env fail in env\n", 16);
	return (1);
}

int	ft_create_env_list_lib(char **env)
{
	t_env	*envi;
	t_env	*new;
	t_env	*head;
	int		counter;

	envi = ((counter = 0), NULL);
	while (env[counter])
	{
		new = (t_env *)ft_lstnew(NULL);
		if (!new)
			return (free_env_l(&envi));
		ft_lstadd_back((t_list **)&envi, (t_list *)new);
		counter ++;
	}
	head = envi;
	counter = 0;
	while (envi)
	{
		envi->content = create_env_value(env[counter]);
		if (envi->content == NULL)
			return (free_env_l(&envi));
		envi = envi->next;
		counter ++;
	}
	while(head)
	{
		printf("%s%s\n", head->content->key, head->content->value);
		head = head->next;
	}
	return (0);
}
