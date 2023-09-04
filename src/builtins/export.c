/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/04 16:57:35 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "structs.h"


///     0 ==== mo es alfanumerico
///     1 ==== es alfanumerico

void	order_env(t_env envi)

int	ft_export(char *var, t_env  *envi)
{
	int		count;
	t_env	*new;

	count = 0;
	if (!var)
		order_env(envi);
	while (var[count] && (ft_isalnum(var[count]) || var[count] == '_'))
		count ++;
	if (var[count])
	{
		ft_errors("export: ", var);
		perror("");
		return (1);
	}
	else
	{
		new = ft_calloc(1, sizeof (t_env));
		new->content = create_env_var(var);
		new->next = NULL;
		ft_lstadd_back(envi, new);
	}
	return (0);
}
