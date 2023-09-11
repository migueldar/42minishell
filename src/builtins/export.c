/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/11 19:57:35 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "structs.h"
#include "env.h"

void	verifless(t_env	*env_cpy, char *printverif, int iter)
{
	t_env	*enviprint;
	int		positionprint;

	positionprint = iter;
	enviprint = env_cpy;
	while (env_cpy)
	{
		if (ft_strncmp(enviprint->content->key, env_cpy->content->key, \
			ft_strlen(enviprint->content->key)) > 0)
		{
			if (!printverif[iter])
			{
				positionprint = iter;
				enviprint = env_cpy;
			}
		}
		env_cpy = env_cpy->next;
		iter ++;
	}
	print_export(enviprint);
	printverif[positionprint] = '1';
}

int	no_args_export(t_env *envi)
{
	char	*printverif;
	t_env	*env_cpy;
	int		len;
	int		iter;

	len = ft_lstsize((t_list *) envi);
	printverif = ft_calloc(sizeof(char), len);
	if (!printverif)
		return (perror("minishell"), 1);
	while (len--)
	{
		iter = 0;
		env_cpy = envi;
		while (printverif[iter])
		{
			iter++;
			env_cpy = env_cpy->next;
		}
		verifless(env_cpy, printverif, iter);
	}
	free (printverif);
	return (0);
}

char	*selectkey(char *var)
{
	char	*copyfindkey;
	int		counter;

	counter = 0;
	while (var[counter])
		counter ++;
	copyfindkey = ft_calloc(counter + 1, sizeof(char));
	if (!copyfindkey)
		return (perror("minishell: "), NULL);
	counter = 0;
	while (var[counter] && var[counter] != '=')
	{
		copyfindkey[counter] = var[counter];
		counter ++;
	}
	return (copyfindkey);
}

int	create_varexport(t_env	**envi, char *var)
{
	t_env		*new;
	char		*findkey;

	findkey = selectkey(var);
	if (!findkey)
		return (1);
	if (ft_contains_key(*envi, findkey))
	{
		if (var[ft_strlen(findkey)] || var[ft_strlen(findkey) + 1])
			single_unset(envi, findkey);
		else
			return (free(findkey), 0);
	}
	new = ft_calloc(1, sizeof (t_env));
	if (!new)
		return ((free (findkey)), perror(""), 1);
	new->content = create_env_var(var);
	if (!new->content)
		return (free(new), (free(findkey)), perror(""), 1);
	ft_lstadd_back((t_list **)envi, (t_list *)new);
	free (findkey);
	return (0);
}

// cuando nobre no permitido exit code a 1
int	ft_export( t_env **envi, t_string_l *var)
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
