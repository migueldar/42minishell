/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:21:48 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/15 11:30:04 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins.h"

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
