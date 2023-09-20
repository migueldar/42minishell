/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/20 14:24:39 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*fork_free_command_l(t_command_l **command_l, int which)
{
	int			counter;
	t_command	*fork_command;
	t_command_l	*head;

	counter = 0;
	head = *command_l;
	while (*command_l)
	{
		if (counter == which)
		{
			fork_command = (*command_l)->cmd;
			(*command_l)->cmd = NULL;
		}
		(*command_l) = (*command_l)->next;
		counter ++;
	}
	ft_lstclear_cmd_l(&head);
	return (fork_command);
}


int	single_forked_cmd(t_env **env, t_command_l *cmd)
{
	printf("antes\n");
	int		pid;
	char *programPath = "/bin/ls";
	char *args[] = {programPath, "-l", "-a", "/bin", NULL};
	char **envi;
	//if (find path(env, cmd->cmd->args->content)
	//{
		envi = env_to_array(*env);
		if (!envi)
			return (1);
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			//redirecciones
			if (handle_redirs(cmd->cmd->redirs))
				return(1);
			// printf("redir == %s\n", cmd->cmd->redirs->redir->where);
			printf("soy un hijo\n");
			if (execve(programPath, args, envi) == -1)
			{
				perror("minishell"); // Si ocurre un error, imprime un mensaje de error
        		exit(1);
    		}
			ft_lstclear_cmd_l(&cmd);
			ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
			clear_history();
			//ejecutar
			//if no se ha podido verificar liberamos ¿en padre?
		}
		else
		{
			printf("soy el padre\n");
			wait(NULL);

		}
		printf("despues\n");
		return(0);
	//}
	return (1);
}
