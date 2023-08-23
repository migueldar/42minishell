/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/08/23 21:13:44 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "builtins.h"

char *get_pwd(t_env *env)
{
    while(env)
    {
        if(ft_strncmp(env->content->key, "PWD", 3) == 0)
            break ;
        env = env->next;
    }
    if(env)
        return(env->content->value);
    return(NULL);
}

int ft_pwd(void)
{
    char *pwd;
    
    pwd = NULL;
    getcwd(pwd, 0);
    printf("%s\n", pwd);
    perror("getcwd");
    if(pwd == NULL)
        return(1);
    printf("%s\n", pwd);
    return(0);
}

