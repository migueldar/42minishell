/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:57:25 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/21 22:29:46 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "command.h"
# include <libft.h>

int		ft_isspace(char c);
int		ft_isoperator(char c);
void	free_arr_2(void **fr);
void	command_l_printer(t_command_l *in);

#endif