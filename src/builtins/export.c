/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/12 17:53:52 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "structs.h"
#include "env.h"

void	verify_alpha_smaller(t_env *env_cpy, char *print_verif, int iter)
{
	t_env	*envi_print;
	int		position_print;

	position_print = iter;
	envi_print = env_cpy;
	while (env_cpy)
	{
		if (ft_strncmp(envi_print->content->key, env_cpy->content->key, \
			ft_strlen(envi_print->content->key)) > 0)
		{
			if (!print_verif[iter])
			{
				position_print = iter;
				envi_print = env_cpy;
			}
		}
		env_cpy = env_cpy->next;
		iter ++;
	}
	single_print_export(envi_print);
	print_verif[position_print] = '1';
}

int	no_args_export(t_env *envi)
{
	char	*print_verif;
	t_env	*env_cpy;
	int		len;
	int		iter;

	len = ft_lstsize((t_list *) envi);
	print_verif = ft_calloc(sizeof(char), len);
	if (!print_verif)
		return (perror("minishell"), 1);
	while (len--)
	{
		iter = 0;
		env_cpy = envi;
		while (print_verif[iter])
		{
			iter++;
			env_cpy = env_cpy->next;
		}
		verify_alpha_smaller(env_cpy, print_verif, iter);
	}
	free(print_verif);
	return (0);
}

char	*select_key(char *var)
{
	char	*copy_find_key;
	int		counter;

	counter = 0;
	while (var[counter])
		counter++;
	copy_find_key = ft_calloc(counter + 1, sizeof(char));
	if (!copy_find_key)
		return (perror("minishell"), NULL);
	counter = 0;
	while (var[counter] && var[counter] != '=')
	{
		copy_find_key[counter] = var[counter];
		counter++;
	}
	return (copy_find_key);
}

int	create_varexport(t_env **envi, char *var)
{
	t_env		*new;
	char		*find_key;

	find_key = select_key(var);
	if (!find_key)
		return (1);
	if (ft_contains_key(*envi, find_key))
	{
		if (var[ft_strlen(find_key)])
			single_unset(envi, find_key);
		else
			return (free(find_key), 0);
	}
	new = ft_calloc(1, sizeof (t_env));
	if (!new)
		return (free(find_key), perror("minishell"), 1);
	new->content = create_env_var(var);
	if (!new->content)
		return (free(new), free(find_key), perror("minishell"), 1);
	ft_lstadd_back((t_list **)envi, (t_list *)new);
	free(find_key);
	return (0);
}

int	ft_export(t_env **envi, t_string_l *var)
{
	int			count;
	int			status;

	status = 0;
	if (!var)
		return (no_args_export(*envi));
	while (var)
	{
		count = 0;
		while (var->content[count] && (ft_isalnum(var->content[count]) \
			|| var->content[count] == '_') && var->content[count] != '=')
			count ++;
		if ((var->content[count] != '=' && var->content[count]) \
			|| ft_isdigit(var->content[0]) || var->content[0] == '=')
		{
			status = 1;
			ft_errors_export(var->content);
		}
		else
			if (create_varexport(envi, var->content))
				return (1);
			var = var->next;
	}
	return (status);
}
