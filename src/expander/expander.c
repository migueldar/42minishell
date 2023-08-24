/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:46:13 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/24 04:21:20 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_exp_l		*dummy2;
	t_string_l	*dummy3;
	int			status;
	
	// ft_print_env(env);
	dummy = expand_argument(cmds->cmd->args->content, env, &status);
	printf("Parameter expansion:\n");
	printf("expanded: %s    wasexpanded: %s\n\n", dummy.content, dummy.was_expanded);
	dummy2 = word_split(dummy);
	printf("Word split:\n");
	print_exp_l(dummy2);
	dummy3 = quote_removal(dummy2);
	printf("\nQuote removal:\n");
	print_string_l(dummy3);
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
