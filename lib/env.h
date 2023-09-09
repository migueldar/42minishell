/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:30:54 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/09 21:18:53 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structs.h"

int	put_valenv(t_env **envi, char *val);
int	lenenv(t_env *env);
int	ft_contains_key(t_env *envi, char *fkey);
int	ft_new_key(t_env **envi, char *val);

#endif