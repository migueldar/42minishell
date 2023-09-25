/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:46:13 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/24 22:35:16 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_string_l	*fully_expand_arg_print(char *arg, t_env *env)
// {
// 	t_exp_str	dummy;
// 	t_exp_l		*dummy2;
// 	t_string_l	*dummy3;
// 	int			status;

// 	status = 0;
// 	// ft_print_env(env);
// 	printf("Parameter expansion:\n");
// 	dummy = expand_argument(arg, env, &status);
// 	if (status)
// 		return NULL;
// 	printf("expanded: %s    wasexpanded: %s\n\n", dummy.content, dummy.was_exp);
// 	printf("Word split:\n");
// 	dummy2 = word_split(dummy);
// 	if (!dummy2)
// 		return NULL;
// 	print_exp_l(dummy2);
// 	printf("\nQuote removal:\n");
// 	dummy3 = quote_removal(dummy2);
// 	if (!dummy3)
// 		return NULL;
// 	print_string_l(dummy3);
// }

// NULL if fail
//status 0 malloc fail
//status 1 ok but expanded to NULL
t_string_l	*fully_expand_arg(char *arg, t_env *env, int *status)
{
	t_exp_str	exp_arg;
	t_exp_l		*splitted_arg;
	t_string_l	*ret;

	*status = 0;
	exp_arg = expand_argument(arg, env, status);
	if (*status)
		return (*status = 0, NULL);
	if (!*status && !exp_arg.content)
		return (*status = 1, NULL);
	splitted_arg = word_split(exp_arg, status);
	free_exp_str(exp_arg);
	if (!splitted_arg)
		return (NULL);
	ret = quote_removal(splitted_arg);
	ft_lstclear_exp_l(&splitted_arg);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*expand_redir(char *arg, t_env *env, int *status)
{
	t_string_l	*exp;
	char		*ret;

	exp = fully_expand_arg(arg, env, status);
	if (!exp && !*status)
		return (*status = 0, NULL);
	if (ft_lstsize((t_list *) exp) != 1)
		return (*status = 1, ft_lstclear((t_list **) &exp, free), NULL);
	ret = ft_strdup(exp->content);
	ft_lstclear((t_list **) &exp, free);
	return (ret);
}

//return NULL if fail
//stat 0 malloc fail
//stat 1 ambigous redirect
static t_redir_l	*expand_redirs(t_redir_l *redirs, t_env *env, int *stat)
{
	t_redir_l	*ret;
	t_redir_l	*new_n;

	*stat = 0;
	ret = NULL;
	while (redirs)
	{
		new_n = ft_calloc(1, sizeof(t_redir_l));
		if (!new_n)
			return (ft_lstclear_redir_l(&ret), NULL);
		new_n->redir = ft_calloc(1, sizeof(t_redir));
		if (!new_n->redir)
			return (ft_lstclear_redir_l(&ret), free(new_n), NULL);
		if (redirs->redir->flag != HERE_DOC)
			new_n->redir->where = expand_redir(redirs->redir->where, env, stat);
		else
			new_n->redir->where = ft_strdup(redirs->redir->where);
		if (!new_n->redir->where)
			return (free(new_n->redir), ft_lstclear_redir_l(&ret),
				free(new_n), NULL);
		new_n->redir->flag = redirs->redir->flag;
		ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		redirs = redirs->next;
	}
	return (*stat = 0, ret);
}

//status 0 malloc fail
//status 1 ok but expanded to NULL
static t_string_l	*expand_args(t_string_l *args, t_env *env, int *status)
{
	t_string_l	*ret;
	t_string_l	*new_n;

	ret = NULL;
	while (args)
	{
		*status = 0;
		new_n = fully_expand_arg(args->content, env, status);
		if (!new_n && *status == 0)
			return (ft_lstclear((t_list **) &ret, free), NULL);
		if (new_n)
			ft_lstadd_back((t_list **) &ret, (t_list *) new_n);
		args = args->next;
	}
	return (ret);
}

//return NULL if fail
//status 0 malloc fail
//status 1 ambigous redirect
t_command_l	*expander(t_command_l *cmds, t_env *env, int *status)
{
	t_command_l	*ret;
	t_command_l	*aux;

	ret = NULL;
	while (cmds)
	{
		aux = ft_calloc(1, sizeof(t_command_l));
		if (!aux)
			return (ft_lstclear_cmd_l(&ret), NULL);
		aux->cmd = ft_calloc(1, sizeof(t_command));
		if (!aux->cmd)
			return (ft_lstclear_cmd_l(&ret), free(aux), NULL);
		aux->cmd->args = expand_args(cmds->cmd->args, env, status);
		if (!aux->cmd->args && cmds->cmd->args && *status == 0)
			return (ft_lstclear_cmd_l(&ret), free(aux->cmd), free(aux), NULL);
		aux->cmd->redirs = expand_redirs(cmds->cmd->redirs, env, status);
		if (!aux->cmd->redirs && cmds->cmd->redirs)
			return (ft_lstclear_cmd_l(&ret),
				ft_lstclear((t_list **) &(aux->cmd->args), free),
				free(aux->cmd), free(aux), NULL);
		ft_lstadd_back((t_list **) &ret, (t_list *) aux);
		cmds = cmds->next;
	}
	return (ret);
}
