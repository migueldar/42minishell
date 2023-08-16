/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:27:04 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/15 22:46:23 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_DEBUG_H
# define MALLOC_DEBUG_H

# ifndef MALLOC_FAIL
#  define MALLOC_FAIL 0
# endif

# include <string.h>

void	*malloc(size_t n);
void	leaks(void);

#endif