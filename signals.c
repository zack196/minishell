/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:35:39 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 02:11:59 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parse.h"

void	sig_int_handler(int s)
{
	(void)s;
	g_heredoc_interrupted = 3;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	count_consecutive_dollars(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			count++;
			continue ;
		}
		if (count)
			break ;
		str++;
	}
	return (count);
}

void	ft_minishell(t_envi **env, t_token **token, t_cmd **cmd)
{
	t_token	*tmp;

	tmp = NULL;
	handler_expand(token, *env, *token);
	remove_spaces(token, *token);
	if (check_syntax(*token, tmp))
		parse_cmd(token, cmd, env);
	else
		ft_lstclear_t(token);
}
