#include "../../minishell.h"

static void    err(char *input)
{
    printf("exit\n");
    printf("bash: exit: %s: numeric argument required", input);
	exit(255);
}

void    env_exit(char *exit_num)
{
    int i;

    i = -1;
	if (exit_num[i + 1] == '-' || exit_num[i + 1] == '+')
		i++;
    while (exit_num[++i])
        if (!ft_isdigit(exit_num[i]))
            err(exit_num);
	i = ft_atoi(exit_num);
	printf("exit\n");
	exit(i);
}