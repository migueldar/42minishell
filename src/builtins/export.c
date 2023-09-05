/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/05 20:02:27 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "structs.h"


///     0 ==== mo es alfanumerico
///     1 ==== es alfanumerico

static void	ft_errors_export(char *function, char *content, int p)
{
	write(2, "minishell: ", 11);
	write(2, function, ft_strlen(function));
	write(2, "'", 1);
	write(2, content, ft_strlen(content));
	write(2, "'", 1);
	write(2, ": ", 2);
	if (p)
		perror("");
}

void	swap_export(t_env	**envi)
{
	t_env_var	*swap;

	swap = (*envi)->next->content;
	(*envi)->next->content = (*envi)->content;
	(*envi)->content = swap;
}

t_env	*search_head(t_env *envi)
{
	int		minlen;
	t_env	*head;

	head = envi;
	while (envi)
	{
		if (ft_strlen(envi->content->key) < ft_strlen(head->content->key))
			minlen = ft_strlen(envi->content->key);
		else
			minlen = ft_strlen(head->content->key);
		if (ft_strncmp(envi->content->key, head->content->key, minlen) < 0)
			head = envi;
		envi = envi->next;
	}
	return (head);
}

static void	print_export(t_env *envi)
{
	while (envi)
	{
		if (envi->content)
		{
			write(1, "declare -x ", 11);
			if (envi->content->value)
				printf("%s=\"%s\"\n", envi->content->key, envi->content->value);
			else
				printf("%s\n", envi->content->key);
		}
		envi = envi->next;
	}
}

void	order_env(t_env *envi)
{
	t_env	*cm;
	int		minlen;
	t_env	*head;

	head = envi;
	while (envi)
	{
		cm = head;
		while (cm && cm->next)
		{
			if (ft_strlen(cm->content->key) < ft_strlen(cm->next->content->key))
				minlen = ft_strlen(cm->content->key);
			else
				minlen = ft_strlen(cm->next->content->key);
			if (cm->next && ft_strncmp(cm->content->key, cm->next->content->key, minlen) > 0)
			{
				swap_export(&cm);
			}
			cm = cm->next;
		}
		envi = envi->next;
	}
	print_export(head);
}

int	ft_export(t_string_l *var, t_env  *envi)
{
	int		count;
	t_env	*new;

	count = 0;
	if (!var)
		order_env(envi);
	else
	{
		while (var->content[count] && (ft_isalnum(var->content[count]) || var->content[count] == '_' ) &&  var->content[count] != '=')
			count ++;
		if ((var->content[count] && var->content[count] != '=') || ft_isdigit(var->content[0]))
		{
			ft_errors_export("export: ", var->content, 0);
			write(2, "not a valid identifier\n", 23);
			return (1);
		}
		else
		{
			new = ft_calloc(1, sizeof (t_env));
			if(var->content[count])
				new->content = create_env_var(var->content);
			new->content = create_env_var(var->content);
			new->next = NULL;
			ft_lstadd_back((t_list **)&envi, (t_list *)new);
		}
	}
	return (0);
}
