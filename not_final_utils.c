#include "utils.h"

void	cmd_args_printer(char *str)
{
	printf("\n\t%s", str);
}

void	cmd_redir_printer(t_redir *redir)
{
	printf("\n\t%d to %s  ", redir->flag, redir->where);
}

void	command_l_printer(t_command_l *in)
{
	int counter = 1;

	while (in)
	{
		printf("Command %d:\n    args:", counter);
		ft_lstiter((t_list *) in->cmd->args, (void (*)(void *)) cmd_args_printer);
		printf("\n    redirs:");
		ft_lstiter((t_list *) in->cmd->redirs, (void (*)(void *)) cmd_redir_printer);
		printf("\n\n");
		counter++;
		in = in->next;
	}	
}
