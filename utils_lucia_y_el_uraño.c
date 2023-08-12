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

void    ft_env(t_env *envi)
{
	while(envi)
	{
		printf("%s%s\n", envi->key, envi->value);
		envi = envi->next;
	}
}
