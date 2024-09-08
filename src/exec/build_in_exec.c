/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:51:55 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/07 22:15:35 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	sp_cmp(char *str)
{
	if (str[0] == '\1' && str[1] == '\0')
		return (1);
	return (0);
}

int	is_build(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] && sp_cmp(cmd[i]) == 1)
		i++;
	if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "echo"))
		return (1);
	else if (cmd && !ft_strcmp(*cmd, "unset"))
		return (1);
	else if (cmd && cmd[i] && !ft_strcmp(cmd[i], "export"))
		return (1);
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "env"))
		return (1);
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "exit"))
		return (1);
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "pwd"))
		return (1);
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "cd"))
		return (1);
	else
		return (0);
}

int	build_in(char **cmd, t_envi **envi)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] && !*cmd[i])
		i++;
	if (cmd && cmd[i] && !ft_strcmp(cmd[i], "export"))
		return (export(cmd + i + 1, envi));
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "echo"))
		return (_echo(cmd + i + 1, envi));
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "unset"))
		return (unset(cmd + 1, envi));
	else if (cmd && cmd[i] && !ft_strcmp(cmd[i], "env"))
		return (env(*envi));
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "pwd"))
		return (pwd(*envi));
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "cd"))
		return (cd(cmd[i + 1], envi));
	else if (cmd && cmd[i] &&!ft_strcmp(cmd[i], "exit"))
		return (_exit_(cmd + i + 1, envi));
	return (0);
}

void	clean_build_files(int fd_in, int fd_out
		, int save_stdin, int save_stdout)
{
	if (fd_in != STDIN_FILENO)
	{
		close(fd_in);
		dup2(save_stdin, STDIN_FILENO);
	}
	if (fd_out != STDOUT_FILENO)
	{
		close(fd_out);
		dup2(save_stdout, STDOUT_FILENO);
	}
	close(save_stdin);
	close(save_stdout);
}

void	build_in_exe(t_cmd *cmd, t_envi **env)
{
	int		fd_in;
	int		fd_out;
	int		save_stdin;
	int		save_stdout;
	char	**cmd_prim;

	cmd_prim = remove_empty_string(cmd->cmd);
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	handel_red(cmd, &fd_in, &fd_out);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (free(cmd_prim), set_exit_status(1, env));
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (free(cmd_prim), set_exit_status(1, env));
	build_in(cmd_prim, env);
	free(cmd_prim);
	clean_build_files(fd_in, fd_out, save_stdin, save_stdout);
}
