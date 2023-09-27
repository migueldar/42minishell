/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:52:09 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/27 16:58:08 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//max exit code is MAX_LONG, min is MIN_LONG
//if exit code is different print error, exit 255
int	ft_exit(t_string_l *args)
{
	int	ret;
	int	status;

	write(2, "exit\n", 5);
	if (ft_lstsize((t_list *) args) == 0)
		return (ST_EXIT | g_exit_status);
	ret = ft_atol(args->content, &status) & 0xff;
	if (status)
	{
		write(2, "minishell: exit: ", 17);
		write(2, args->content, ft_strlen(args->content));
		write(2, ": numeric argument required\n", 28);
		return (ST_EXIT | ST_NON_NUM_EXIT);
	}
	if (ft_lstsize((t_list *) args) > 1)
		return (write(2, "minishell: exit: too many arguments\n", 36), 1);
	return (ST_EXIT | ret);
}
