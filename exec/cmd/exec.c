#include "../../minishell.h"
#include "../../parse/parser.h"

// travereser les cmd
	//put the redirections
	//handel pipe
	//execute cmds
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


void	handel_red(t_cmd *cmd, int *fd_in, int *fd_out)
{
	t_redi	*red;

	red = cmd->in;
	while (red)
	{
		*fd_in = open(red->file, O_RDONLY , 0777);
		if (*fd_in == -1)
		{
			perror(red->file);
			my_malloc(2, 1); // free heap
			exit(1);
		}
		red = red->next;
		if (red)
			close(*fd_in);
	}
	red = cmd->out;
	while (red)
	{
		if (red->type == out)
			*fd_out = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (red->type == append)
			*fd_out = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*fd_out == -1)
		{
			perror(red->file);
			my_malloc(2, 1); // free heap
			exit(1);
		}
		red = red->next;
		if (red)
			close(*fd_out);
	}
}

int	exe_1st_cmd(t_env *sh_env, t_cmd *cmd)
{
	int		fd_pipe[2];
	pid_t	pid;
	int		fd_in;
	int		fd_out;

	if (pipe(fd_pipe))
	{
		perror("error pipe");
		my_malloc(2, 1); // free heap
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("error fork");
		my_malloc(2, 1); // free heap
		exit(1);
	}
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_in = STDIN_FILENO;
		fd_out = fd_pipe[1];
		handel_red(cmd, &fd_in, &fd_out);
		if (cmd->next == NULL)
		{
			if (cmd->out)
				proc(fd_in, fd_out, sh_env, cmd->cmd);
			proc(fd_in, STDOUT_FILENO, sh_env, cmd->cmd);
		}
		proc(fd_in, fd_pipe[1], sh_env, cmd->cmd);
	}
	close(fd_pipe[1]);
	if (!cmd->next)
	{
		close(fd_pipe[0]);
		return (-1);
	}
	return(fd_pipe[0]);
}

int	exe_med_cmd(t_env *sh_env, t_cmd *cmd, int fd)
{
	int		fd_pipe[2];
	pid_t	pid;
	int 	fd_out;

	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_out = fd_pipe[1];
		handel_red(cmd, &fd, &fd_out);// how to check if fd is a file discriptor??
		proc(fd, fd_out, sh_env, cmd->cmd);
	}
	return( close(fd_pipe[1]), close(fd), fd_pipe[0]);
}

void	exe_last_cmd(t_env *sh_env, t_cmd *cmd, int fd)
{
	pid_t	pid;
	int 	fd_out;

	pid = fork();
	if (pid == 0)
	{
		fd_out = STDOUT_FILENO;
		handel_red(cmd, &fd, &fd_out);
		proc(fd, fd_out, sh_env, cmd->cmd);
	}
	close(fd);
}


void	execution(t_env *sh_env, t_cmd *cmd)
{
	int	nbr_cmds;
	int	fd;
	int	i;
	pid_t pid;

	nbr_cmds = nbr_cmd(cmd);
	fd = exe_1st_cmd(sh_env, cmd);
	cmd = cmd->next;
	while (cmd && cmd->pipe)
	{
		fd = exe_med_cmd(sh_env, cmd, fd);
		cmd = cmd->next;
	}
	if (cmd)
		exe_last_cmd(sh_env, cmd, fd);
	while (nbr_cmds--)
		wait(NULL);
}
