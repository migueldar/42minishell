/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:22:36 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/26 00:32:39 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_putendl_n_fd(char *s, int fd, int n)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	if (n == 1)
		write(fd, "\n", 1);
}

char	*ft_getenv(t_env	*envi, char *arr)
{
	while (envi)
	{
		if (ft_strncmp(envi->content->key, arr, ft_strlen(arr) + 1) == 0)
			return (envi->content->value);
		envi = envi->next;
	}
	return (NULL);
}

void	ft_printf_args(t_string_l *args)
{
	while (args)
	{
		printf("print args == %s\n", args->content);
		args = args->next;
	}
}

void	ft_print_array_bi(char **array)
{
	int	y;

	y = 0;
	while (array[y])
	{
		printf("array  ==  %s\n", array[y]);
		y ++;
	}
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
