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
int	handel_red_in(t_cmd *cmd)
{
	t_redi	*red_in;
	int		fd_in;

	red_in = cmd->in;
	// if (!red_in)
		
	// fd_in = open()

}
int	exe_1st_cmd(t_env *sh_env, t_cmd *cmd)
{
	int		fd_pipe[2];
	pid_t	pid;

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
		// handel_red_in(cmd);
		if (cmd->next == NULL)
			proc(STDIN_FILENO, STDOUT_FILENO, sh_env, cmd->cmd);
		proc(STDIN_FILENO, fd_pipe[1], sh_env, cmd->cmd);
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

	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		close(fd_pipe[0]);
		//handel red
		proc(fd, fd_pipe[1], sh_env, cmd->cmd);
	}
	close(fd_pipe[1]);
	close(fd);
	return (fd_pipe[0]);
}

void	exe_last_cmd(t_env *sh_env, t_cmd *cmd, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		//handel red
		proc(fd, STDOUT_FILENO, sh_env, cmd->cmd);
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
	exe_last_cmd(sh_env, cmd, fd);
	while (nbr_cmds--)
		wait(NULL);
}
