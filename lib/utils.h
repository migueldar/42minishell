/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:57:25 by mde-arpe          #+#    #+#             */
<<<<<<< HEAD:lib/utils.h
/*   Updated: 2023/08/22 20:53:38 by mde-arpe         ###   ########.fr       */
=======
/*   Updated: 2023/08/21 22:29:46 by lucia-ma         ###   ########.fr       */
>>>>>>> makefile hecho:libraries/utils.h
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "command.h"
<<<<<<< HEAD:lib/utils.h
# include "libft.h"
=======
# include <libft.h>
>>>>>>> makefile hecho:libraries/utils.h

int		ft_isspace(char c);
int		ft_isoperator(char c);
void	free_arr_2(void **fr);
void	command_l_printer(t_command_l *in);
char	*protected_strjoin(char *s1, char *s2);
int		protected_strlen(char const *str);
char	*protected_strcharjoin(char *str, char c);

#endif