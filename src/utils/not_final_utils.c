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

void	print_exp_l(t_exp_l *in)
{
	int counter = 1;

	while (in)
	{
		printf("Param %d: %s   wasexpanded: %s\n", counter++, in->content->content, in->content->was_exp);
		in = in->next;
	}
}

void	print_string_l(t_string_l *in)
{
	int counter = 1;

	while (in)
	{
		printf("Param %d: %s\n", counter++, in->content);
		in = in->next;
	}
}

void	ft_printf_args(t_string_l *args)
{
	while (args)
	{
		printf("print args == %s\n", args->content);
		args = args->next;
	}
}

void	ft_print_array_bi(char **array)
{
	int	y;

	y = 0;
	while (array[y])
	{
		printf("array  ==  %s\n", array[y]);
		y ++;
	}
}
