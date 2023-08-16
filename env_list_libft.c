/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/16 02:23:48 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	*ft_free_key_value(void *key_value)
{
	t_env_var *k_v_to_free;

	k_v_to_free = key_value;
	free(k_v_to_free->key);
	free(k_v_to_free->value);
	free(k_v_to_free);
	write(2, "malloc env fail\n", 16);

}

t_env_var	*create_key_value(char *env, t_env **envi)
{
	t_env_var		*key_value;
	int				lkey;
	int				aux;

	aux = ((lkey = 0),0);
	key_value = ft_calloc(sizeof(t_env_var *), 1);
	while (env[lkey] && env[lkey] != '=')
		lkey ++;
	key_value->key = ft_calloc(sizeof(char), lkey + 1);
	if (key_value->key == NULL)
		return ((ft_lstclear(envi, ft_free_key_value)), NULL);
	while (lkey --)
	{
		key_value->key[aux] = env[aux];
		aux ++;
	}
	aux = ((env += aux), 0);
	key_value->value = ft_calloc(ft_strlen(env), sizeof(char));
	if (key_value->key == NULL)
		return ((ft_lstclear(envi, ft_free_key_value)), NULL);
	while (env[aux])
	{
		key_value->value[aux] = env[aux];
		aux ++;
	}
	return (key_value);
}

int	ft_create_env_list_lib(char **env)
{
	t_env	*envi;
	t_env	*new;
	t_env	*head;
	int		counter;

	counter = 0;
	envi = NULL;
	while (env[counter])
	{
		new = ft_lstnew(NULL);
		if (!new)
			return (write(2, "malloc env fail in env\n", 16));
		ft_lstadd_back(&envi, new);
		counter ++;
	}
	head = envi;
	counter = 0;
	while (envi)
	{
		envi->content = create_key_value(env[counter], &envi);
		if (envi->content == NULL)
			return (write(2, "malloc env fail in env\n", 16));

		envi = envi->next;
		counter ++;
	}
	while (head)
	{
		printf("%s%s\n", head->content->key, head->content->value);
		head = head->next;
	}
	return (0);
}
