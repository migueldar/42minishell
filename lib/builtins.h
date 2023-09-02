/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:27:41 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/09 02:35:35 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "structs.h"
# include <stdio.h>
# include "utils.h"

int		ft_env(t_env *envi);
t_env	*create_env_list(char **env);
int		ft_echo(t_string_l *argv);
int		ft_pwd(void);
int		ft_cd(t_env	*envi, t_string_l *args);
int		ft_unset(t_env **env, t_string_l *args);
int		single_unset(t_env **env, char *var);
void	free_env_var(t_env_var *env_var);
int		is_builtin(char *cmd);

#endif