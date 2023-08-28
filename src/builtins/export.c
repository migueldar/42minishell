/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/28 18:42:12 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


///     0 ==== mo es alfanumerico
///     1 ==== es alfanumerico

int	ft_export(char *var, t_env  *envi)
{
    if (!var)
        ///printeas env
    while (*var && (ft_isalnum(*var) || *var == '_'))
        var ++;
    if (*var)
    {
        
	    perror("");
        return(1)
    }
    return(0);
}
