/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:23:39 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/05 22:52:31 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, str + i, 1);
		i++;
	}
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	echo_n(char **av, int i)
{
	while (av[i] && check_n(av[i]))
		i++;
	while (av[i])
	{
		ft_putstr(av[i++]);
		if (av[i])
			write(1, " ", 1);
	}
}

int	_echo(char **av, t_envi **envi)
{
	int	i;

	i = 0;
	if (av[i] && check_n(av[i]))
		echo_n(av, i);
	else
	{
		while (av[i])
		{
			ft_putstr(av[i++]);
			if (!av[i])
				break ;
			write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (set_exit_status(0, envi), 0);
}
