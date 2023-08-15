/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/16 00:03:56 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	*ft_free_key_value(void *key_value)
{
	t_envlista_key *k_v_to_free;

	k_v_to_free = key_value;
	free(k_v_to_free->key);
	free(k_v_to_free->value);
	free(k_v_to_free);
	write(2, "malloc env fail\n", 16);
}

t_envlista_key	*create_key_value(char *env, t_list **envi)
{
	t_envlista_key	*key_value;
	int				lkey;
	int				aux;

	printf("aaaaa\n");
	lkey = 0;
	aux = 0;
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
	env += aux;
	aux = 0;
	key_value->value = ft_calloc(ft_strlen(env), sizeof(char));
	if (key_value->key == NULL)
		return ((ft_lstclear(envi, ft_free_key_value)), NULL);
	while (env[aux])
	{
		key_value->value[aux] = env[aux];
		aux ++;
	}
	printf("key == %s\nvalue == %s\n", key_value->key, key_value->value);
	return (key_value);
}

int	ft_create_env_list_lib(char **env)
{
	t_list	*envi;
	t_list	*old;
	t_list	*aux;
	int		counter;

	counter = 0;
	envi = ft_lstnew(env[counter]);
	if(envi == NULL)
		return(1);
	while (env[counter])
	{
		ft_lstadd_back(&envi, ft_lstnew(create_key_value(env[counter], &envi)));
		counter ++;
	}
	/*while(envi)
	{
		//printtf("key == %s\n  value == %s\n", envi)
		printf("envi == %s\n", envi->content);
		envi = envi->next;
	}*/
	return (0);
}
