/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:57:25 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/04 19:34:59 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
# include "libft.h"

void		ft_errors(char *function, char *content, int p);
void		ft_print_array_bi(char **array);
char		*ft_getenv(t_env *envi, char *arr, int *status);
void		ft_printf_args(t_string_l *args);
void		ft_printerror(int first, char *s, int n);
int			ft_isspace(char c);
int			ft_isoperator(char c);
void		free_arr_2(void **fr);
void		command_l_printer(t_command_l *in);
char		*protected_strjoin(char *s1, char *s2);
size_t		protected_strlen(char const *str);
char		*protected_strcharjoin(char *str, char c);
int			is_empty(char const *str);
void		cmd_args_printer(char *str);
int			lst_addback_append(t_string_l **head, t_string_l *add);
char		*full_string(char c, size_t n);
void		print_exp_l(t_exp_l *in);
void		print_string_l(t_string_l *in);

#endif