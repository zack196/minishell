#include "../../includes/parse.h"

void	_process(char **cmd, int fd_in, int fd_out, t_envi *envi)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("\nerror dup");
		return ;
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("error dup2\n");
		return ;
	}
	exe_cmd(cmd, envi);
}

int	exe_first_cmd(t_cmd *cmd, t_envi *envi, char **files)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];

	if (pipe(fd_pipe))
		return (perror("minishell: pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"),close(fd_pipe[0]), close(fd_pipe[1]), -1);
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_in = STDIN_FILENO;
		fd_out = fd_pipe[1];
		if (!cmd->next)
			fd_out = STDOUT_FILENO;
		handel_red(cmd, &fd_in, &fd_out, files);
		if ((cmd->cmd))
			_process(cmd->cmd, fd_in, fd_out, envi);
	}
		if (cmd && !cmd->next)
			return (close(fd_pipe[1]), close(fd_pipe[0]), -1);
		return (close(fd_pipe[1]), fd_pipe[0]);
}

int	cmd_med(t_cmd *cmd, t_envi *envi, int fd_in, char **files)
{
    int     fd_out;
    int     fd_pipe[2];
    pid_t   pid;

	if (pipe(fd_pipe))
	{
		perror("pipe err\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), close(fd_pipe[1]), close(fd_pipe[0]), close(fd_in),-1);
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_out = fd_pipe[1];
		handel_red(cmd, &fd_in, &fd_out, files);
		_process(cmd->cmd, fd_in, fd_out, envi);
	}
	return (close(fd_pipe[1]), close(fd_in), fd_pipe[0]);
}

void	last_cmd(t_cmd *cmd, t_envi *envi, int fd_in, char **files)
{
	pid_t	pid;
	int		fd_out;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		close(fd_in);
		return ;
	}
	if (pid == 0)
	{
		fd_out = STDOUT_FILENO;
		handel_red(cmd, &fd_in, &fd_out, files);
		_process(cmd->cmd, fd_in, fd_out, envi);
	}
	close(fd_in);
}

void	piping(t_cmd *cmd, int fd, t_envi **envi, char **heredoc_files)
{
	if (cmd->cmd)
			fd = exe_first_cmd(cmd, *envi, heredoc_files);
		if (cmd)
			cmd = cmd->next;
		while (cmd && cmd->next && fd != -1)
		{
			fd = cmd_med(cmd, *envi, fd, heredoc_files);
			cmd = cmd->next;
		}
		if (cmd && fd != -1)
			last_cmd(cmd, *envi, fd, heredoc_files);
}
