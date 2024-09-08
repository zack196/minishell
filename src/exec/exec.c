/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:52:47 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 00:24:32 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_envi	*replace_unserscore(t_envi **envi, char *last)
{
	t_envi	*node;
	char	*env_var;

	env_var = ft_strjoin(ft_strdup("_="), last);
	node = *envi;
	while (node)
	{
		if (ft_strcmp(node->key, "_") == 0)
		{
			free(node->value);
			node->value = ft_strdup(last);
			free(env_var);
			return (node);
		}
		node = node->next;
	}
	return (free(env_var), node);
}

void	add_last_argument_to_env(char **cmd, t_envi **envi)
{
	char	*last;
	t_envi	*node;
	int		i;

	i = 0;
	if ((envi && *envi && !ft_strcmp((*envi)->key, "?")
			&& !(*envi)->next) || (*envi)->empty_once)
	{
		(*envi)->empty_once = 1;
		return ;
	}
	while (cmd[i + 1])
		i++;
	last = cmd[i];
	node = replace_unserscore(envi, last);
	if (!node)
		ft_lstadd_back_env(envi, ft_lstnew_env(ft_strdup("_"),
				ft_strdup(last), 0));
}

void	ft_wait(t_cmd *cmd, t_envi **envi)
{
	int	status;

	while (cmd)
	{
		if (cmd->pid == -1)
			break ;
		waitpid(cmd->pid, &status, 0);
		if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			g_heredoc_interrupted = 10;
			set_exit_status(130, envi);
		}
		else if (WTERMSIG(status) == 3)
		{
			write(1, "QUIT : 3\n", 9);
			g_heredoc_interrupted = 10;
			set_exit_status(131, envi);
		}
		else if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status), envi);
		else if (WIFSIGNALED(status))
			set_exit_status(128 + WTERMSIG(status), envi);
		cmd = cmd->next;
	}
}

void	sig_int_(int s)
{
	(void)s;
	g_heredoc_interrupted = 3;
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	_exec(t_cmd *cmd, t_envi **envi)
{
	int		fd;

	signal(SIGINT, sig_int_);
	if (!cmd || !cmd->cmd || cmd->err)
		return ;
	if (cmd && !cmd->next && cmd->cmd)
		add_last_argument_to_env(cmd->cmd, envi);
	else
	{
		free(find_node(*envi, "_")->value);
		find_node(*envi, "_")->value = NULL;
	}
	if (!(cmd && !(cmd->err)))
		return ;
	fd = STDIN_FILENO;
	if (cmd->cmd && !cmd->next && is_build(cmd->cmd))
	{
		cmd->cmd = exec_expand(cmd->cmd);
		return (build_in_exe(cmd, envi));
	}
	piping(cmd, fd, envi);
	ft_wait(cmd, envi);
}
