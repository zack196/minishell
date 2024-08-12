#include "../../minishell.h"

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, STDOUT_FILENO);
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
			write(1, " ", STDOUT_FILENO);
	}
	if (flag_n == 0)
		write(1, "\n", STDOUT_FILENO);
}
