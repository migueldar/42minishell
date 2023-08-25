/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:27:41 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/26 00:32:53 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//# include "minishell.h"
#include "libft.h"
#include "structs.h"
#include "stdio.h"


typedef struct s_env_var
{
	char	*key;
	char	*value; 
}	t_env_var;

typedef struct s_env
{
	t_env_var		*content;
	struct s_env	*next;
}	t_env;

void	ft_putendl_n_fd(char *s, int fd, int n);
char	*ft_getenv(t_env	*envi, char *arr);
void	ft_printf_args(t_string_l *args);
void	ft_print_env(t_env *envi);
t_env	*create_env_list(char **env);
void	ft_print_array_bi(char **array);
void	ft_env(t_env *envi);
int		ft_echo(char **argv);
int		ft_pwd(void);
int     ft_cd(t_env	*envi, t_string_l *args);
void	free_env_var(t_env_var *env_var);

#endif