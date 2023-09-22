/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:18:16 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/09/22 22:31:57 by lucia-ma         ###   ########.fr       */
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

int	childs_tasks(char **envi, t_env **env, t_command_l *cmd)
{
	char *programPath = "/bin/ls";
	char *args[] = {programPath, "-l", "-a", NULL};

	if (handle_redirs(cmd->cmd->redirs))
		return(1);
	// printf("redir == %s\n", cmd->cmd->redirs->redir->where);
	ft_lstclear_cmd_l(&cmd);
	ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
	clear_history();
	if (execve(programPath, args, envi) == -1)
	{
		perror("minishell"); // Si ocurre un error, imprime un mensaje de error
		exit(1);
    }
	return (0);
}

int	cmd_size(t_command_l *cmd)
{
	int	len;
	
	len = 0;
	while(cmd)
	{
		len ++;
		cmd = cmd->next;
	}
	return (len);
}

int	create_pipes(int ***pipes_fd, int len)
{
	int	counter;

	counter = 0;
	(*pipes_fd) = malloc(len * sizeof(int *));
	if (!(*pipes_fd))
		return(1);
	while (len--)
	{
		(*pipes_fd)[counter] = malloc(2 * sizeof(int));
		if (!(*pipes_fd)[counter] || pipe((*pipes_fd)[counter]) < 0)
		{
			return (1);
		}
		counter ++;
	}
	return(0);
}
void print_arraynum(int **nums)
{
	printf("%d %d\n", nums[0][0], nums[0][1]);	
	printf("%d %d\n", nums[1][0], nums[1][1]);
}

int	manage_pipes(int position_child, int **pipes_fd, int number_commands)
{
	if (position_child == 0)
	{
		printf("primer \n");
		if (handle_dups(-2, pipes_fd[position_child][1]))
			return(1);
	}
	if (position_child > 0 && position_child < number_commands)
	{
		printf("medio\n");
		if (handle_dups(pipes_fd[position_child - 1][0], pipes_fd[position_child][1]))
			return(1);
	}
	if (position_child == number_commands)
	{
		printf("final\n");
		if (handle_dups(pipes_fd[position_child - 1][0], -2))
			return(1);
	}
	return(0);
}

int	manage_pipes_and_forks(t_env **env, t_command_l	*cmd)
{
	char	**envi;
	int		pid;
	int		position_child;
	int		**pipes_fd;
	int		len;
	
	position_child = 0;
	envi = env_to_array(*env);
	pipes_fd = NULL;
	if (!envi )
		return (perror("minishell"), 1);
	
	if (create_pipes(&pipes_fd, cmd_size(cmd) - 1))
		return (perror("minishell"), 1);
	len = cmd_size(cmd);
	
	while (cmd)
	{
		pid = fork();
		if(pid < 0)
			return(1);
		if(pid == 0)
		{
			printf("len %d\n", len);
			if (manage_pipes(position_child, pipes_fd, len - 1))
			{
				ft_lstclear_cmd_l(&cmd);
				ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
				clear_history();
				return(perror("minishell"), 1);
			}
			if (childs_tasks(envi, env, cmd))
			{
				ft_lstclear_cmd_l(&cmd);
				ft_lstclear((t_list **) env, (void (*)(void *)) free_env_var);
				clear_history();
			}
		}
		position_child ++;
		cmd = cmd->next;
	}
	if(pid > 0)
		while (len --)
			wait(NULL);
	return (0);
}