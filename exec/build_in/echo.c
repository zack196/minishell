#include "../../minishell.h"

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void	echo(char **argv, int flag_n)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		ft_putstr(argv[i++]);
		if (argv[i])
			write(1, " ", 1);
	}
	if (flag_n == 0)
		write(1, "\n", 1);
}
