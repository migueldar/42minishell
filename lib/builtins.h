/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:27:41 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/28 19:30:52 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "stdio.h"
# include "libft.h"
# include "structs.h"

void	ft_print_env(t_env *envi);
t_env	*create_env_list(char **env);
void	ft_print_array_bi(char **array);
void	ft_env(t_env *envi);
int		ft_echo(char **argv);
int		ft_pwd(void);
int     ft_cd(int argc, char **argv, char **env);
void	free_env_var(t_env_var *env_var);
int		ft_export(char *var, t_env  *envi);

#endif