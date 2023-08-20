/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:46:13 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/20 22:41:09 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if var doesnt exist in env returns ""
// returns null if malloc fails
char	*expand_var(char *var, t_env *env)
{
	if (!var)
		return (NULL);
	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(g_exit_status));
	if (!ft_strncmp(var, "$", 2))
		return (ft_strdup("$"));
	while (env)
	{
		if (!ft_strncmp(var, env->content->key, ft_strlen(var) + 1))
			return (ft_strdup(env->content->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

//when enter here, $ is already gone
char	*expand_substring(char **str, t_env *env, char in_quote)
{
	char	*to_expand;
	char	*aux;
	char	*ret;

	if (ft_isalpha((*str)[0]) || (*str)[0] == '_')
	{
		to_expand = NULL;
		while (ft_isalnum(**str) || (**str == '_'))
		{
			aux = protected_strcharjoin(to_expand, **str);
			free(to_expand);
			if (!aux)
				return (NULL);
			to_expand = aux;
			(*str)++;
		}
		ret = expand_var(to_expand, env);
		free(to_expand);
		return (ret);
	}
	else if ((*str)[0] == '?')
		return ((*str)++, expand_var("?", env));
	else if (((*str)[0] == 0x22 || (*str)[0] == 0x27) && !in_quote)
		return (ft_strdup(""));
	return (expand_var("$", env));
}

int	expand_dollar(char **str, t_env *env, char in_quote, t_string_l **curr)
{
	char		*aux;
	t_string_l	*list_to_add;
	int			status;
	
	(*str)++;
	aux = expand_substring(str, env, in_quote);
	(*str)--;
	if (!aux)
		return (1);
	list_to_add = split_to_list(aux);
	free(aux);
	if (!list_to_add)
		return (1);
	status = lst_addback_append(curr, list_to_add);
	if (status)
		ft_lstclear((t_list **) &list_to_add, free);
	return (status);
}

t_string_l	*expand_string(char *str, t_env *env)
{
	t_string_l	*ret;
	char		*aux;
	char		in_quote;
	int			status;

	ret = (in_quote = 0, ft_calloc(1, sizeof (t_string_l)));
	if (!ret)
		return (NULL);
	while (*str)
	{
		if (in_quote && *str == in_quote)
			in_quote = 0;
		else if (!in_quote && (*str == 0x22 || *str == 0x27))
			in_quote = *str;
		else if (*str == '$' && in_quote != 0x27)
		{
			status = expand_dollar(&str, env, in_quote, &ret);
			if (status)
				return (ft_lstclear((t_list **) &ret, free), NULL);
		}
		else
		{
			aux = protected_strcharjoin(ft_lstlast((t_list *) ret)->content, *str);
			free(ft_lstlast((t_list *) ret)->content);
			if (!aux)
				return (NULL);
			ft_lstlast((t_list *) ret)->content = aux;
		}
		str++;
	}
	return (ret);
}

static t_redir_l	*expand_redirs(t_redir_l *redirs, t_env *env)
{
	t_redir_l	*ret;
	
	ret = NULL;
	(void) env;
	while (redirs)
	{
		redirs = redirs->next;
	}
	return (ret);
}

static t_string_l	*expand_args(t_string_l *args, t_env *env)
{
	t_string_l	*ret;
	int			counter;

	(void) env;
	ret = NULL;
	counter = 0;
	while (args)
	{
		if (args->content)
		args = args->next;
	}
	return (ret);
}

//only error this can give is malloc fail
//expands and gets rid of quotes
//idk exactly how but take into count empty command, maybe in executer
t_command_l *expander(t_command_l *cmds, t_env *env)
{
	t_command_l	*ret;
	t_command_l	*aux;
	t_string_l	*dummy;
	
	dummy = expand_string(cmds->cmd->args->content, env);
	ft_lstiter((t_list *) dummy, (void (*)(void *)) cmd_args_printer);
	//free(dummy);
	ret = NULL;
	while (cmds && NULL)
	{
		aux = ft_calloc(1, sizeof(t_command_l));
		if (!aux)
			return (NULL); // lstclear ret
		aux->cmd = ft_calloc(1, sizeof(t_command));
		if (!aux->cmd)
			return (free(aux), NULL); // lstclear ret
		aux->cmd->args = expand_args(cmds->cmd->args, env);
		if (!aux->cmd->args)
			return (free(aux->cmd), free(aux), NULL); // lstclear ret
		aux->cmd->redirs = expand_redirs(cmds->cmd->redirs, env);
		if (!aux->cmd->redirs)
			return (free(aux->cmd->redirs), free(aux->cmd), free(aux), NULL); // lstclear ret
		cmds = cmds->next;
	}
	return (ret);
}
