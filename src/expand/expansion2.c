/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:34:40 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 13:03:47 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	check_exp(t_token *tok, t_envi *env)
{
	(void)env;
	if (tok->type == HYPHEN)
	{
		hyphen_exp(tok, env);
		if (!tok->content)
			return ;
	}
	else if ((tok->type == DOUBLE || tok->type == WORD)
		&& ft_strlen(tok->content) > 1)
	{
		if (*(tok->content) == '$')
			tok->expand = 1;
		expand_var(env, &tok->content);
	}
}

void	set_type(t_token *tok)
{
	if (tok->type == WORD)
		tok->type = SINGLE_EXP;
	else
		tok->type = SINGLE;
}

void	here_doc_exp(t_token *token)
{
	while (token)
	{
		if (*token->content == '$' && ft_strlen(token->content) == 1)
		{
			if (token->next && (token->next->type == DOUBLE
					|| token->next->type == SINGLE))
				(1) && (free(token->content), token->content = ft_strdup(""));
		}
		else if (ft_strlen(token->content) == 2 && token->type == OPR
			&& ft_strcmp(token->content, "<<") == 0)
		{
			if (token->next && token->next->type == SPACEE)
			{
				if (token->next->next && token->next->next->type != PIPE
					&& token->next->next->type != OPR)
					set_type(token->next->next);
			}
			else if (token->next && token->next->type != PIPE
				&& token->next->type != OPR)
				set_type(token->next);
		}
		token = token->next;
	}
}

int	join_str(t_token **token, t_token *tmp)
{
	if ((*token)->type == PIPE || (*token)->type == OPR
		|| (*token)->type == SPACEE)
		return (0);
	if (!tmp || tmp->type == PIPE || tmp->type == OPR
		|| tmp->type == SPACEE)
		return (0);
	else
	{
		tmp->content = ft_strjoin(tmp->content, (*token)->content);
		tmp->next = (*token)->next;
		ft_lstdelone_t(*token);
		*token = tmp->next;
		return (1);
	}
}

void	handler_expand(t_token **token, t_envi *env, t_token *tok)
{
	t_token	*tmp;

	(void)env;
	(void)token;
	tmp = NULL;
	trim_quotes(*token);
	here_doc_exp(*token);
	while (tok)
	{
		check_exp(tok, env);
		if (join_str(&tok, tmp) == 0)
		{
			tmp = tok;
			tok = tok->next;
		}
	}
}
