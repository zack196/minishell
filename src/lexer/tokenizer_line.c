/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:08:26 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 00:10:47 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	whish_separator(char *line)
{
	if (*line == '|')
		return (1);
	if (*line == 32 || (*line >= 9 && *line <= 12))
		return (2);
	if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
		return (3);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}

int	type_token(char *content)
{
	if (*content == '\'')
		return (SINGLE);
	if (*content == '\"')
		return (DOUBLE);
	if (*content == '|')
		return (PIPE);
	if (content[0] && content[1] && !ft_strncmp(content, "<<", 2))
		return (OPR);
	if (content[0] && content[1] && !ft_strncmp(content, ">>", 2))
		return (OPR);
	if (*content == '<' || *content == '>')
		return (OPR);
	if (*content == '~' && ft_strlen(content) == 1)
		return (HYPHEN);
	if (*content == ' ')
		return (SPACEE);
	else
		return (WORD);
}

int	take_separator(char *line, t_token **token)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 12) || line[i] == 32))
		i++;
	if (i && *token)
		ft_lstadd_back_m(token, ft_lstnew_m(ft_strdup(" ")));
	if (whish_separator(line + i) == 1)
	{
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line + i, 0, 1)));
		return (i + 1);
	}
	if (whish_separator(line + i) == 3)
	{
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line + i, 0, 2)));
		return (i + 2);
	}
	return (i);
}

int	with_quotes(char *line, t_token **token, int c, int *flag)
{
	int	i;

	i = 1;
	while (line [i] && line[i] != c)
		i++;
	if (line[i] != c)
	{
		ft_putstr_fd("eroooor  ", 2);
		*flag = 0;
		return (0);
	}
	if (i)
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line, 0, i + 1)));
	return (i + 1);
}

int	take_word(char *line, t_token **token, int *flag)
{
	int	i;

	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		return (with_quotes(line, token, *line, flag));
	if (whish_separator(line + i))
		return (0);
	while (line[i] && !whish_separator(line + i)
		&& line[i] != '\'' && line[i] != '\"')
		i++;
	if (i)
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line, 0, i)));
	if (line[i] == '\"' || line[i] == '\'')
	{
		if (*token && (*token)->next)
			(*token)->next->next_starts_with_quote = 1;
	}
	return (i);
}
