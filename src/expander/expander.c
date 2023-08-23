/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:46:13 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/23 03:30:54 by mde-arpe         ###   ########.fr       */
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

t_exp_str	expand_dollar(char **str, t_env *env, char in_quote, int *status)
{
	t_exp_str	ret;

	(*str)++;
	ret.content = expand_substring(str, env, in_quote);
	(*str)--;
	if (!ret.content)
		return (*status = 1, ret);
	ret.was_expanded = full_string('1', ft_strlen(ret.content));
	if (!ret.was_expanded)
		return (*status = 1, ret);
	return (*status = 0, ret);
}

t_exp_str	expand_string(char *str, t_env *env, int *status)
{
	t_exp_str	ret;
	t_exp_str	aux;
	t_exp_str	aux2;
	char		in_quote;

	ret.content = NULL;
	ret.was_expanded = NULL;
	in_quote = 0;
	while (*str)
	{
		if (in_quote && *str == in_quote)
			in_quote = 0;
		else if (!in_quote && (*str == 0x22 || *str == 0x27))
			in_quote = *str;
		if (*str == '$' && in_quote != 0x27)
		{
			aux = expand_dollar(&str, env, in_quote, status);
			if (*status)
				return (ret);
			aux2.content = protected_strjoin(ret.content, aux.content);
			free(ret.content);
			free(aux.content);
			aux2.was_expanded = protected_strjoin(ret.was_expanded, aux.was_expanded);
			free(ret.was_expanded);
			free(aux.was_expanded);
			if (!aux2.content || !aux2.was_expanded)
				return (*status = 1, ret);
			ret = aux2;
		}
		else
		{
			aux.content = protected_strcharjoin(ret.content, *str);
			aux.was_expanded = protected_strcharjoin(ret.was_expanded, '0');
			free(ret.content);
			free(ret.was_expanded);
			if (!aux.content || !aux.was_expanded)
				return (*status = 1, ret);
			ret = aux;
		}
		str++;
	}
	return ret;
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
	t_exp_str	dummy;
	int			status;
	
	dummy = expand_string(cmds->cmd->args->content, env, &status);
	printf("expanded: %s\nwasexpanded: %s\n", dummy.content, dummy.was_expanded);
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
