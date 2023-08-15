/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma < lucia-ma@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:27:41 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/15 21:35:51 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}t_env;

typedef struct s_envlista_key
{
	char            *key;
	char            *value; 
}t_envlista_key;



int     ft_create_env_list(char **env);
void	ft_print_array_bi(char **array);
void    ft_env(t_env *envi);
int		ft_echo(char ** argv);
char    *get_pwd(char **env);
int     *ft_pwd(char **env);
int     ft_cd(int argc, char **argv, char **env);



#endif