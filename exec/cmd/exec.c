#include "../../minishell.h"
#include "../../parse/parser.h"

void	_exec(t_env *sh_env, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		exec_cmd(sh_env, cmd->cmd);
	}
	wait(NULL);
	printf("in\n");
}
int	open_red(t_redi *red)
{
	int	fd;

	if (red->type == in)
		fd = open(red->file, O_RDONLY, 0777);
	else if (red->type == out)
		fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (red->type == append)
		fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

	// travereser les cmd
		//put the redirections
		//handel pipe
		//execute cmds
void	execution(t_env *sh_env, t_cmd *cmd)
{
	int		fd_in;
	int		fd_pipe[2];
	pid_t	pid;
	int		fd_out;

	while (cmd)
	{
		pipe(fd_pipe);
		pid = fork();
		fd_in = STDIN_FILENO;
		fd_out = STDOUT_FILENO;
		if (pid == 0)
		{
			if (cmd->in)
			{
				if (cmd->in->type == in)
					fd_in = open(cmd->in->file, O_RDONLY, 0777);
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (cmd->out)
			{
				if (cmd->out->type == out)
					fd_out = open(cmd->out->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				else if (cmd->out->type == append)
					fd_out = open(cmd->out->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			close(fd_pipe[0]);
			dup2(fd_in, STDIN_FILENO);
			dup2(fd_pipe[1], fd_out);
			exec_cmd(sh_env, cmd->cmd);
		}
		fd_in = fd_pipe[1];
		close(fd_pipe[0]);
		wait(NULL);
		cmd = cmd->next;
	}
}
