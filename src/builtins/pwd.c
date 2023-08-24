/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/24 14:06:33 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int ft_pwd(void)
{
    char *pwd;
    
    pwd = NULL;
    pwd = getcwd(pwd, 0);
    if(pwd == NULL)
        return(1);
    printf("%s\n", pwd);
    return(0);
}

