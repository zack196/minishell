/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:25:05 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 12:51:52 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	is_last_in(t_redi *red)
{
	red = red->next;
	while (red && (red->type != in && red->type != heredoc))
		red = red->next;
	if (!red)
		return (1);
	return (0);
}

int	is_last_out(t_redi *red)
{
	red = red->next;
	while (red && (red->type != out && red->type != append))
		red = red->next;
	if (!red)
		return (1);
	return (0);
}

int	in_red(t_cmd *cmd, int *fd_in, t_redi *red)
{
	if (red->type == in)
		*fd_in = open(red->file, O_RDONLY);
	else if (red->type == heredoc && is_last_in(red) == 1)
		*fd_in = cmd->fd_hdoc;
	if (*fd_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(red->file);
		return (0);
	}
	if (is_last_in(red) == 0 && red->type != heredoc)
		close(*fd_in);
	return (1);
}

int	out_red(int *fd_out, t_redi *red)
{
	if (red->type == out)
		*fd_out = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->type == append)
		*fd_out = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(red->file);
		return (0);
	}
	if (!is_last_out(red))
		close(*fd_out);
	return (1);
}

int	handel_red(t_cmd *cmd, int *fd_in, int *fd_out)
{
	t_redi		*red;
	int			i;

	red = cmd->red;
	while (red)
	{
		if (red->type == in || red->type == heredoc)
		{
			i = in_red(cmd, fd_in, red);
			if (i == 0)
				return (0);
		}
		if (red->type == out || red->type == append)
		{
			i = out_red(fd_out, red);
			if (i == 0)
				return (0);
		}
		red = red->next;
	}
	return (1);
}
