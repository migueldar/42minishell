#include "builtins.h"

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
