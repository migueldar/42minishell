/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/09 02:44:26 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	put_valenv(t_env **envi, char *val)
{
	if(*val)
	{
		val ++;
		if((*envi)->content->value)
			free((*envi)->content->value);
		(*envi)->content->value = ft_strdup(val);
		printf("put_valenv == %s\n", (*envi)->content->value);
		if (!(*envi)->content->value)
			return (perror("minishell: "), 1);
	}
	return (0);
}

int	lenenv(t_env *env)
{
	int	len;

	len = 0;
	while(env)
	{
		len ++;
		env = env->next;
	}
	return (len);
}
