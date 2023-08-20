/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:57:25 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/22 23:03:44 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "command.h"
# include "libft.h"

int		ft_isspace(char c);
int		ft_isoperator(char c);
void	free_arr_2(void **fr);
void	command_l_printer(t_command_l *in);
char	*protected_strjoin(char *s1, char *s2);
size_t	protected_strlen(char const *str);
char	*protected_strcharjoin(char *str, char c);
int		is_empty(char const *str);

#endif