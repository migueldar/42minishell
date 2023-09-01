/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:22:36 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/01 20:26:45 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishel.h"
#include "utils.h"

void	ft_printerror(int first, char *s, int n)
{
	if (!s)
		return ;
	if (first == 1)
		write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	if (n == 1)
		write(2, "\n", 1);
}

//return NULL if fail
//status 0 malloc fail
//status 1 not found
char	*ft_getenv(t_env *envi, char *arr, int *status)
{
	while (envi)
	{
		if (ft_strncmp(envi->content->key, arr, ft_strlen(arr) + 1) == 0)
		{
			if (!envi->content->value)
				break ;
			return (ft_strdup(envi->content->value));
		}
		envi = envi->next;
	}
	return (*status = 1, NULL);
}

void	ft_print_env(t_env *envi)
{
	while (envi)
	{
		printf("%s=%s\n", envi->content->key, envi->content->value);
		envi = envi->next;
	}
}

// takes NULLS as len 0
char	*protected_strcharjoin(char *str, char c)
{
	char	*ret;
	int		counter;

	ret = ft_calloc(protected_strlen(str) + 2, 1);
	if (ret == NULL)
		return (NULL);
	counter = 0;
	while (str && str[counter])
	{
		ret[counter] = str[counter];
		counter++;
	}
	ret[counter] = c;
	return (ret);
}

int	is_empty(char const *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

/*void    ft_env(t_env *envi)
{
	while(envi)
	{
		printf("%s%s\n", envi->key, envi->value);
		envi = envi->next;
	}
}*/
