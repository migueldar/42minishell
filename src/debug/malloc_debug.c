/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:25:57 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/25 19:16:08 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MALLOC_DEBUG

#include "minishell.h"
#include "malloc_debug.h"

void leaks() {
	system("leaks -q minishell");
}

void	*malloc(size_t n)
{
	static int cnt = 0;

	
	if (cnt == MALLOC_FAIL) {
		// void	*ptr[100];
		// int		size;
		
		// size = backtrace(ptr, 100);
		// backtrace_symbols_fd(ptr, size, 1);
		return (NULL);
	}
	cnt++;
	return (calloc(n, 1));
}

#endif