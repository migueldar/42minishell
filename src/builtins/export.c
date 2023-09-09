/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:21:06 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/09 16:35:53 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "structs.h"
#include "env.h"


///     0 ==== mo es alfanumerico
///     1 ==== es alfanumerico

static void	ft_errors_export(char *content)
{
	write(2, "minishell: ", 11);
	write(2, "export: ", 8);
	write(2, "`", 1);
	write(2, content, ft_strlen(content));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid identifier\n", 23);
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
	if (envi->content)
	{
		write(1, "declare -x ", 11);
		if (envi->content->value)
			printf("%s=\"%s\"\n", envi->content->key, envi->content->value);
		else
			printf("%s\n", envi->content->key);
	}
}


void	print_isverif(int len, char *s)
{
	int count;
	
	count = 0;
	while(len--)
	{
		printf(" %c  ", s[count]);
		printf("a");
		count ++;
		
	}
	printf("\n");
}

void	verifless(t_env	*env_cpy,  char *printverif, int iter)
{
	t_env *enviprint;
	int positionprint;

	positionprint  = iter;
	enviprint = env_cpy;
	while (env_cpy)
	{
		if (ft_strncmp(enviprint->content->key, env_cpy->content->key, ft_strlen(enviprint->content->key)) > 0)
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
	while(len--)
	{
		iter = 0;
		env_cpy = envi;
		while(printverif[iter])
		{
			iter++;
			env_cpy = env_cpy->next;
		}
		verifless(env_cpy, printverif, iter);
	}
	return (0);
}

int	ft_new_key(t_env **envi, char *findkey)
{
	while(*envi && ft_strncmp((*envi)->content->key, findkey, ft_strlen(findkey) + 1))
		*envi = (*envi)->next;
	if(*envi)
	{
		free((*envi)->content->value);
		(*envi)->content->value = ft_strdup(findkey);
		if(!(*envi)->content->value)
			return(1);
	}
	return(0);
}

int	ft_contains_key(t_env *envi, char *findkey, int *status)
{
	char *copyfindkey;
	int counter;
	
	counter = 0;
	while(findkey[counter] && findkey[counter] != '=')
		counter ++;	
	copyfindkey = ft_calloc(counter + 1, sizeof(char));
	if(!copyfindkey)
		return(perror("minishell: "), 1);
	counter = 0;
	while(findkey[counter] && findkey[counter] != '=')
	{
		copyfindkey[counter] = findkey[counter];
		counter ++;
	}
	*status = 0;
	while(envi && ft_strncmp((envi)->content->key, findkey, counter))
		envi = (envi)->next;
	if(envi)		
		*status = -1;
	return(0);
}

int	create_varexport(t_env	**envi, char *var, int count)
{
	t_env		*new;
	int			status;
	
	(void) count;
	if(ft_contains_key(*envi, var, &status))
		return(1);
	if(status)
		ft_unset(NULL, NULL);
	new = ft_calloc(1, sizeof (t_env));
	if (!new)
		return(perror(""), 1);
	new->content = create_env_var(var);
	if (!new->content)
		return(free(new), perror(""), 1);
	ft_lstadd_back((t_list **)envi, (t_list *)new);
	return (0);
}

// cuando nobre no permitido exit code a 1
int	ft_export(t_string_l *var, t_env **envi)
{
	int			count;
	
	if (!var)
		return (no_args_export(*envi));
	else
	{
		while(var)
		{
			count = 0;
			while (var->content[count] && (ft_isalnum(var->content[count]) || var->content[count] == '_' ) &&  var->content[count] != '=')
				count ++;
			if ((var->content[count] != '=' && var->content[count]) || ft_isdigit(var->content[0]))
				ft_errors_export(var->content);
			else
				if (create_varexport(envi, var->content, count))
					return (1);
			var = var->next;
		}
	}
	return (0);
}