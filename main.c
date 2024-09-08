/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:37:16 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 15:17:33 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parse.h"

void	term_attr(struct termios *att)
{
	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, att))
		perror("termios");
}

void	parce_exec(t_token *token, t_envi *dup_env, t_cmd *cmd)
{
	ft_minishell(&dup_env, &token, &cmd);
	if (here_doc(&cmd, dup_env) == 1)
		_exec(cmd, &dup_env);
	close_hdoc(cmd);
	clear_cmds(&cmd);
}

void	main_loop(t_token *token, t_envi *dup_env, t_cmd *cmd, char *line)
{
	struct termios	att;

	while (1)
	{
		(1) && (token = NULL, cmd = NULL);
		sig();
		line = readline("minishell> ");
		if (g_heredoc_interrupted == 3)
		{
			set_exit_status(1, &dup_env);
			g_heredoc_interrupted = 0;
		}
		if (!line)
			exit(1);
		if (line[0])
			add_history(line);
		term_attr(&att);
		if (token_line(line, &token, 0))
			parce_exec(token, dup_env, cmd);
		free(line);
		if (isatty(STDIN_FILENO) && tcsetattr(0, TCSANOW, &att))
			perror("termios");
	}
}

void	close_hdoc(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_hdoc != -1)
		{
			close(cmd->fd_hdoc);
		}
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_token	*token;
	t_envi	*dup_env;
	t_cmd	*cmd;
	char	*line;

	dup_env = NULL;
	line = NULL;
	check_args(ac, av, &dup_env, env);
	token = NULL;
	cmd = NULL;
	rl_catch_signals = 0;
	main_loop(token, dup_env, cmd, line);
	ft_free_env(&dup_env);
}
