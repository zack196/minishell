/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:08:22 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 00:07:30 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	error_format(t_token *token, t_token *tmp, int i)
{
	if (i)
	{
		if (tmp->type == OPR && token->type == OPR)
			return (
				ft_ptndl("syntax error near unexpected token",
					token->content, 2));
		if (tmp->type == OPR && token->type == PIPE)
			return (
				ft_ptndl("syntax error near unexpected token",
					token->content, 2));
		if (tmp->type == PIPE && token->type == PIPE)
			return (
				ft_ptndl("syntax error near unexpected token",
					token->content, 2));
		if (tmp->type == PIPE && token->type == OPR
			&& (!token->next || token->next->type == OPR
				|| token->next->type == PIPE))
			return (
				ft_ptndl("syntax error near unexpected token",
					token->content, 2));
	}
	return (1);
}

int	find_error(t_token *token, t_token *tmp)
{
	if ((tmp->type == PIPE || tmp->type == OPR)
		&& (token->type == PIPE || token->type == OPR))
	{
		if (!error_format(token, tmp, 1))
			return (0);
	}
	return (1);
}

int	check_syntax(t_token *token, t_token *tmp)
{
	if (token && token->type == PIPE)
		return (ft_ptndl("syntax error near unexpected token", "|", 2));
	if (token && !token->next && (token->type == OPR || token->type == PIPE))
		return (ft_ptndl("syntax error near unexpected token", "newline", 2));
	while (token)
	{
		if ((!ft_strcmp(token->content, "&&")
				|| !ft_strcmp(token->content, "&"))
			&& token->type == WORD)
			return (ft_ptndl("syntax error near unexpected token", "&", 2));
		if ((!ft_strcmp(token->content, ";")
				|| !ft_strcmp(token->content, ";;"))
			&& token->type == WORD)
			return (ft_ptndl("syntax error near unexpected token", ";", 2));
		if (tmp && !find_error(token, tmp))
			return (0);
		tmp = token;
		token = token->next;
	}
	if (tmp && (tmp->type == OPR || tmp->type == PIPE))
		return (ft_ptndl("syntax error near unexpected token",
				"newline", 2));
	return (1);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		printf(">>>>%s\n", str[i]);
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	set_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->red = NULL;
	cmd->red = NULL;
	cmd->fd_hdoc = -1;
	cmd->pipe = 0;
}
