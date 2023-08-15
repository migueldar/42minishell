/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/15 21:25:25 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

t_env	*create_key_value(char *env, t_env *old)
{
	t_env	*key_value;
	int		lkey;
	int		aux;

	lkey = 0;
	aux = 0;
	key_value = malloc(sizeof(t_env *));
	while (env[lkey] && env[lkey] != '=')
		lkey ++;
	key_value->key = ft_calloc(sizeof(char), (lkey +1));
	if (key_value->key == NULL)
		perror("fallo de malloc key");
	while (lkey--)
	{
		key_value->key[aux] = env[aux];
		aux ++;
	}
	env += aux;
	aux = 0;
	key_value->value = ft_calloc(ft_strlen(env), sizeof(char));
	if (key_value->key == NULL)
		perror("fallo de malloc value");
	while (env[aux])
	{
		key_value->value[aux] = env[aux];
		aux ++;
	}
	key_value->next = NULL; 
	if (old)
		old->next = key_value;
	return (key_value);
}

int	ft_create_env_list(char **env)
{
	int		counter;
	t_env	*envi;
	t_env	*old;
	t_env	*aux;

	counter = 0;
	envi = create_key_value(env[counter], NULL);
	aux = envi;
	counter ++;
	while (env[counter])
	{
		old = create_key_value(env[counter], aux);
		aux = old;
		counter ++;
	}
	ft_env(envi);
	return (0);
}
