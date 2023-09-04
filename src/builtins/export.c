/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/04 19:29:36 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "structs.h"


///     0 ==== mo es alfanumerico
///     1 ==== es alfanumerico

void	order_env(void)
{
	printf("order env export\n");
}

int	ft_export(t_string_l *var, t_env  *envi)
{
	int		count;
	t_env	*new;

	count = 0;
	if (!var)
		order_env();
	if (ft_isnum(var->content[count]))
		
	while (var->content[count] && (ft_isalnum(var->content[count]) || var->content[count] == '_'))
		count ++;
	printf("despues del while\n");
	print_string_l(var);
	if (var->content[count])
	{
		ft_errors("export: ", var->content);
		perror("");
		return (1);
	}
	else
	{
		new = ft_calloc(1, sizeof (t_env));
		new->content = create_env_var(var->content);
		new->next = NULL;
		ft_lstadd_back((t_list **)&envi, (t_list *)new);
	}
	return (0);
}
