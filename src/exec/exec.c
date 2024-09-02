#include "../../includes/parse.h"

int	count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	add_last_argument_to_env(char **cmd, t_envi **envi)
{
	char	*last;
	char	*env_var;
	t_envi	*node;

	int i = 0;
	while (cmd[i + 1])
		i++;
	last = cmd[i];
	env_var = ft_strjoin(ft_strdup("_="), cmd[i]);
	node = *envi;
	while (node)
	{
		if (ft_strcmp(node->key, "_") == 0)
		{
			free(node->value);
			node->value = ft_strdup(last);
			return (free(env_var));
		}
		node = node->next;
	}
	if (!*envi)
		ft_lstadd_back_env(envi, ft_lstnew_env(ft_strdup("_"), ft_strdup(last), 0));
	free(env_var);
}

void	clean_heredoc(char **heredoc)
{
	int	i;

	i = -1;
	while (heredoc && heredoc[++i])
	{
		unlink(heredoc[i]);
		free(heredoc[i]);
	}
}

void	ft_wait(int nbr_cmd, t_envi **envi)
{
	int	status;

	while (nbr_cmd--)
	{
		wait(&status);
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status), envi);
		else if (WEXITSTATUS(status))
			set_exit_status(WEXITSTATUS(status), envi);
	}
}

void	_exec(t_cmd *cmd, t_envi **envi)
{
	int		fd;
	int		nbr_cmd;
	char	**heredoc_files;

	nbr_cmd = count_cmd(cmd);
	heredoc_files = creat_heredoc(cmd, *envi);
	if (heredoc_files && nbr_cmd == 1 && cmd && cmd->cmd)
		add_last_argument_to_env(cmd->cmd, envi);
	if (heredoc_files && cmd && !(cmd->err))
	{
		fd = STDIN_FILENO;
		if (cmd->cmd && nbr_cmd == 1 && is_build(*(cmd->cmd)))
		{
			build_in_exe(cmd, envi, heredoc_files);
			cmd = cmd->next;
			return (clean_heredoc(heredoc_files), free(heredoc_files));
		}
		set_child_process();
		piping(cmd, fd, envi, heredoc_files);
		ft_wait(nbr_cmd, envi);
	}
	clean_heredoc(heredoc_files);
	free(heredoc_files);
}
