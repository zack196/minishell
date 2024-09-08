/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:35:39 by namrene           #+#    #+#             */
/*   Updated: 2024/09/07 18:50:38 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parse.h"

static	void	handler_heredoc(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 6;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	set_herdoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_heredoc);
}

void	check_args(int ac, char **av, t_envi **dup_env, char **env)
{
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("errror nbrs argmnts", 2);
		exit(1);
	}
	parse_env(env, dup_env);
	set_exit_status(0, dup_env);
}

void	remove_spaces(t_token **token, t_token *tok)
{
	t_token	*tmp;

	tmp = NULL;
	while (tok)
	{
		if (tok->type == SPACEE)
			ft_remove(tmp, &tok, token);
		else
		{
			tmp = tok;
			tok = tok->next;
		}
	}
}

void	ft_free_tab2(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
