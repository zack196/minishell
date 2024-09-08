/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:09:38 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 01:10:21 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	set_exit_status(int status, t_envi **envi)
{
	t_envi	*env_exit;

	env_exit = find_node(*envi, "?");
	free(env_exit->value);
	env_exit->value = ft_itoa(status);
}

int	nbr_arg(char **av)
{
	int	i;

	if (!av && !*av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (str + i);
}

static int	check_arg(char *str, t_envi **envi)
{
	int	i;

	i = 0;
	str = skip_spaces(str);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			set_exit_status(255, envi);
			return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(str, 2)
				, ft_putstr_fd(": numeric argument required\n", 2)
				, exit(255), 0);
		}
		i++;
	}
	return (1);
}

int	_exit_(char **av, t_envi **envi)
{
	int	n;

	ft_putstr_fd("exit\n", 1);
	if (!*av)
		return (set_exit_status(0, envi), exit(0), 0);
	else if (nbr_arg(av) >= 2)
	{
		if (check_arg(*av, envi) == 1)
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
				set_exit_status(1, envi), 1);
	}
	else
	{
		if (check_arg(*av, envi))
		{
			n = ft_atoi(*av);
			if (n == -1 && ft_strcmp("-1", skip_spaces(*av)))
				return (ft_putstr_fd("minishell: exit:", 2)
					, ft_putstr_fd(*av, 2)
					, ft_putstr_fd(": numeric argument required\n", 2)
					, set_exit_status(-1, envi), exit(255), 255);
			return (set_exit_status(n, envi), exit(n), n);
		}
	}
	return (0);
}
