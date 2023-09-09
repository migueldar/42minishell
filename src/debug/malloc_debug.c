/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:25:57 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/02 07:02:58 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "malloc_debug.h"

void leaks()
{
	char *itoaed = ft_itoa(getpid());
	char *commmand = ft_strjoin("leaks -q ", itoaed);

	free(itoaed);
	system(commmand);
	free(commmand);
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