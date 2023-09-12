/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:30:54 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/12 17:10:26 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structs.h"

int	put_valenv(t_env **envi, char *val);
int	ft_contains_key(t_env *envi, char *fkey);
int	ft_new_key(t_env **envi, char *val);

#endif