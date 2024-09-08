/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:24:41 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 00:27:52 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	_process(char **cmd, int fd_in, int fd_out, t_envi *envi)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (exit(1));
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	exe_cmd(cmd, envi, fd_in, fd_out);
	close(fd_in);
	close(fd_out);
}

int	exe_first_cmd(t_cmd *cmd, t_envi *envi)
{
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];

	if (pipe(fd_pipe))
		return (perror("minishell: pipe"), -1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), close(fd_pipe[0]),
			close(fd_pipe[1]), -1);
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(fd_pipe[0]);
		fd_in = STDIN_FILENO;
		fd_out = fd_pipe[1];
		if (!cmd->next)
			fd_out = STDOUT_FILENO;
		handel_red(cmd, &fd_in, &fd_out);
		if (cmd->cmd)
			_process(cmd->cmd, fd_in, fd_out, envi);
	}
	if (cmd && !cmd->next)
		return (close(fd_pipe[1]), close(fd_pipe[0]), -1);
	return (close(fd_pipe[1]), fd_pipe[0]);
}

int	cmd_med(t_cmd *cmd, t_envi *envi, int fd_in)
{
	int	fd_out;
	int	fd_pipe[2];

	if (pipe(fd_pipe))
		return (perror("pipe err\n"), -1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), errno = 0, close(fd_pipe[1]),
			close(fd_pipe[0]), close(fd_in), -1);
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(fd_pipe[0]);
		fd_out = fd_pipe[1];
		handel_red(cmd, &fd_in, &fd_out);
		if (cmd->cmd)
			_process(cmd->cmd, fd_in, fd_out, envi);
	}
	return (close(fd_pipe[1]), close(fd_in), fd_pipe[0]);
}

void	last_cmd(t_cmd *cmd, t_envi *envi, int fd_in)
{
	int		fd_out;

	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		close(fd_in);
		return ;
	}
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		fd_out = STDOUT_FILENO;
		handel_red(cmd, &fd_in, &fd_out);
		if (cmd->cmd)
			_process(cmd->cmd, fd_in, fd_out, envi);
	}
	close(fd_in);
}

void	piping(t_cmd *cmd, int fd, t_envi **envi)
{
	if (cmd)
	{
		fd = exe_first_cmd(cmd, *envi);
		cmd = cmd->next;
	}
	while (cmd && cmd->next && fd != -1)
	{
		fd = cmd_med(cmd, *envi, fd);
		cmd = cmd->next;
	}
	if (cmd && fd != -1)
		last_cmd(cmd, *envi, fd);
}
