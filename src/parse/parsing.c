/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:01:32 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 00:07:04 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	set_oper(t_token *token, t_redi **redir, int type)
{
	if (token)
		ft_lstadd_back_redi(redir,
			ft_lstnew_redi(ft_strdup(token->content), type));
	if (token && type == heredoc && token->type == SINGLE_EXP
		&& token->next_starts_with_quote != 1)
		ft_lstlast_redi(*redir)->must_exp = 1;
}

void	retrive_space(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == 127)
			content[i] = ' ';
		i++;
	}
}

int	check_redir(t_token *token, t_envi **env)
{
	int	len;

	len = ft_strlen(token->content) - 1;
	if (token->expand)
	{
		retrive_space(token->content);
		if (ft_strchr_2(token->content, ' ') && token->content[len] != ' ')
		{
			ft_ptndl("ambigous redirection", NULL, 2);
			set_exit_status(1, env);
			return (1);
		}
		if (!*(token->content) || sp_cmp(token->content) == 1)
		{
			ft_ptndl("ambigous redirection2", NULL, 2);
			set_exit_status(1, env);
			return (1);
		}
	}
	return (0);
}

void	is_operator(t_token *token, t_cmd *cmd, t_envi **env)
{
	if (token->next)
	{
		if (check_redir(token->next, env))
		{
			cmd->err = 1;
			return ;
		}
	}
	if (!ft_strcmp(token->content, "<<"))
		set_oper(token->next, &cmd->red, heredoc);
	else if (*(token->content) == '<')
		set_oper(token->next, &cmd->red, in);
	else if (!ft_strcmp(token->content, ">>"))
		set_oper(token->next, &cmd->red, append);
	else if (*(token->content) == '>')
		set_oper(token->next, &cmd->red, out);
}

void	rub_operator(t_cmd *cmd, t_token *token, t_token **tok, t_envi **env)
{
	t_token	*tmp;
	t_token	*tmp1;

	tmp = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == OPR)
		{
			is_operator(token, ft_lstlast_cmd(cmd), env);
			if (token && token->next)
			{
				tmp1 = token->next->next;
				ft_remove(token, &token->next, tok);
				ft_remove(tmp, &token, tok);
				token = tmp1;
			}
		}
		else
		{
			tmp = token;
			token = token->next;
		}
	}
}
