#include "../../includes/parse.h"

int is_build(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else
		return (0);
}

int	build_in(char **cmd, t_envi **envi)
{
	if (!ft_strcmp(*(cmd), "echo"))
		return (echo(cmd + 1, envi));
	else if (!ft_strcmp(*(cmd), "unset"))
		return unset(cmd + 1, envi);
	else if (!ft_strcmp(*(cmd), "env") && !*(cmd + 1))
		return env(*envi);
	else if (!ft_strcmp(*(cmd), "export"))
		return export(cmd + 1, envi);
	else if (!ft_strcmp(*(cmd), "pwd"))
		return pwd(*envi);
	else if (!ft_strcmp(*(cmd), "cd"))
		return cd(*(cmd + 1), envi);
	else if (!ft_strcmp(*(cmd), "exit"))
		return (_exit_(cmd + 1, envi));
	return (0);
}

void	build_in_exe(t_cmd *cmd, t_envi **env, char **files)
{
	int	fd_in;
	int	fd_out;
	int	save_stdin;
	int	save_stdout;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	handel_red(cmd, &fd_in, &fd_out, files);
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("error dup\n");
		return ;
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("error dup2\n");
		return ;
	}
	build_in(cmd->cmd, env);
	if (fd_in != STDIN_FILENO)
	{
		close(fd_in);
		dup2(save_stdin, STDIN_FILENO);
	}
    if (fd_out != STDOUT_FILENO)
	{
		close(fd_out);
		dup2(save_stdout,STDOUT_FILENO);
	}
	close(save_stdin);
	close(save_stdout);
}
