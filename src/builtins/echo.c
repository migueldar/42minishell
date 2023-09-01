#include "../../lib/builtins.h"
#include <string.h>



int	ft_search_n(char *str)
{
	while (*str && *str == 'n')
		str ++;
	if (*str)
		return (1);
	return (0);
}

void	ft_print_echo(t_string_l *argv)
{
	while (argv)
	{
		write(1, argv->content, ft_strlen(argv->content));
		argv = argv->next;
	}
}

int	ft_echo(t_string_l *argv)
{
	int	count;
	int	verif_n;
	int	salto_de_linea;

	salto_de_linea = 0;
	count = 0;
	if (argv)
	{
		while (argv && strncmp(argv->content, "-n", 2) == 0)
		{
			verif_n = ft_search_n(&argv->content[2]);
			if (verif_n == 1)
				break ;
			salto_de_linea = 1;
			count ++;
			argv = argv->next;
		}
		if (argv->content)
			ft_print_echo(argv);
	}
	if (salto_de_linea == 0)
		write(1, "\n", 1);
	return (0);
}

