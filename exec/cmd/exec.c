#include "../../minishell.h"
#include "../../parse/parser.h"

int	nbr_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

int	exe_1st_cmd(t_env *sh_env, t_cmd *cmd)
{
	int		fd_pipe[2];
	pid_t	pid;
	int		fd_in;
	int		fd_out;

	if (pipe(fd_pipe) == -1)
		error("error pipe");
	pid = fork();
	if (pid == -1)
		error("error fork");
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_in = STDIN_FILENO;
		fd_out = fd_pipe[1];
		handel_red(cmd, &fd_in, &fd_out);
		if (!cmd->next && !cmd->out)
			fd_out = STDOUT_FILENO;
		proc(fd_in, fd_out, &sh_env, cmd->cmd);
	}
	if (!cmd->next)
		return (close(fd_pipe[1]), close(fd_pipe[0]), -1);
	return(close(fd_pipe[1]), fd_pipe[0]);
}

int	exe_med_cmd(t_env *sh_env, t_cmd *cmd, int fd)
{
	int		fd_pipe[2];
	pid_t	pid;
	int 	fd_out;

	if (pipe(fd_pipe) == -1)//check error
		error("error pipe!\n");
	pid = fork();
	if (pid == -1)
		error("fork!\n");
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_out = fd_pipe[1];
		handel_red(cmd, &fd, &fd_out);// how to check if fd is a file discriptor
		proc(fd, fd_out, &sh_env, cmd->cmd);
	}
	return( close(fd_pipe[1]), close(fd), fd_pipe[0]);
}

void	exe_last_cmd(t_env *sh_env, t_cmd *cmd, int fd)
{
	pid_t	pid;
	int 	fd_out;

	pid = fork();
	if (pid == -1)
		error("error forking!");
	if (pid == 0)
	{
		fd_out = STDOUT_FILENO;
		handel_red(cmd, &fd, &fd_out);
		proc(fd, fd_out, &sh_env, cmd->cmd);
	}
	close(fd);
}

void	execution(t_env **sh_env, t_cmd *cmd)
{
	int	nbr_cmds;
	int	fd;
	int	bool_build_in;

	nbr_cmds = nbr_cmd(cmd);
	bool_build_in = 1;
	if (!cmd->pipe)
	{
		exec_build_in(sh_env, cmd->cmd, &bool_build_in);
		if (bool_build_in)
			return ;
	}
	fd = exe_1st_cmd(*sh_env, cmd);
	cmd = cmd->next;
	while (cmd && cmd->pipe)
	{
		fd = exe_med_cmd(*sh_env, cmd, fd);
		cmd = cmd->next;
	}
	if (cmd)
		exe_last_cmd(*sh_env, cmd, fd);
	while (nbr_cmds--)
		wait(NULL);
}
