/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:25:57 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/25 17:34:34 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "malloc_debug.h"

static int	size_of_int(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

static char	*itoa(int n)
{
	char	*ret;
	char	*ret_cpy;
	long	long_n;
	int		div;

	ret = calloc(size_of_int(n) + 1, 1);
	if (ret == NULL)
		return (NULL);
	ret_cpy = ret;
	long_n = n;
	div = 1;
	if (long_n < 0)
	{
		*ret = '-';
		ret++;
		long_n *= -1;
	}
	while (long_n / div > 9)
		div *= 10;
	while (div)
	{
		*(ret++) = '0' + (long_n / div) % 10;
		div /= 10;
	}
	return (ret_cpy);
}

static char	*strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*ret_cpy;

	if (!s1 || !s2)
		return (NULL);
	ret = calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	ret_cpy = ret;
	if (ret == NULL)
		return (NULL);
	while (*s1 != 0)
		*(ret++) = *(s1++);
	while (*s2 != 0)
		*(ret++) = *(s2++);
	return (ret_cpy);
}

void leaks()
{
	char *itoaed = itoa(getpid());
	char *command = strjoin("leaks -q ", itoaed);

	free(itoaed);
	system(command);
	free(command);
}

#ifdef MALLOC_DEBUG

void	*malloc(size_t n)
{
	static int cnt = 0;

	
	if (cnt == MALLOC_FAIL) {
		// void	*ptr[100];
		// int		size;
		
		// size = backtrace(ptr, 100);
		// backtrace_symbols_fd(ptr, size, 1);
		errno = ENOMEM;
		return (NULL);
	}
	cnt++;
	return (calloc(n, 1));
}

#endif