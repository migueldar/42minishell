/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/16 20:44:00 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	if (env_var->key == NULL)
		return (free_env_var(env_var), NULL);
	put_content(length, &env_var->key, &env);
	length = ft_strlen(env);
	env_var->value = ft_calloc(length, sizeof(char));
	if (env_var->value == NULL)
		return (free_env_var(env_var), NULL);
	env ++;
	put_content(length, &env_var->value, &env);
	return (env_var);
}

void	*free_env_l(t_env **envi)
{
	ft_lstclear ((t_list **) &envi, (void (*)(void	*)) free_env_var);
	return (NULL);
}

t_env	*ft_create_env_list(char **env)
{
	t_env	*envi;
	t_env	*new;
	int		counter;

	envi = ((counter = 0), NULL);
	while (env[counter])
	{
		new = (t_env *)ft_lstnew((void *)create_env_var(env[counter]));
		if (!new || new->content == NULL)
		{
			write(2, "malloc env fail in env\n", 16);
			return (free_env_l(&envi));
		}
		ft_lstadd_back((t_list **)&envi, (t_list *)new);
		counter ++;
	}
	ft_print_env(envi);
	return (envi);
}
