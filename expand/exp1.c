#include "parse/parser.h"
#include "minishell.h"

// void	check_tokens(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	printf("--------CHECK_TOKENS-----------\n");
// 	while (tmp)
// 	{
// 		printf("content = %s\n", tmp->content);
// 		printf("type    = %d\n", tmp->type);
// 		tmp = tmp->next;
// 	}
// 	printf("----------------------------\n");
// }

void	trim_quotes(t_token *token)
{
	char	*tmp;

	while (token)
	{
		tmp = token->content;
		if (!*tmp)
		{
			free(tmp);
			token->content = ft_strdup("");
			return ;
		}
		if (token->type == DOUBLE)
		{
			token->content = ft_strtrim(token->content, "\"");
			free(tmp);
		}
		if (token->type == SINGLE)
		{
			token->content = ft_strtrim(token->content, "\'");
			free(tmp);
		}
		token = token->next;
	}
}

char	*get_value_of_exp(t_env *env, char *key)
{
	char	*s;

	if (*key == '?')
	{
		free(key);
		//return code retour de (exit status) de la derniere commande execute
	}
	while (env && ft_strcmp(env->var, key) != 0)
		env = env->next;
	if (env && ft_strcmp(env->var, key) == 0)
	{
		free(key);
		return (ft_strdup(env->val));
	}
	free(key);
	return (NULL);
}

void	hyphen_exp(t_token *tok, t_env *env)
{
	char	*tmp;

	if (tok)
	{
		tmp = tok->content;
		tok->content = get_value_of_exp(env, ft_strdup("HOME"));
		free(tmp);
	}
}


void	check_exp(t_token *tok, t_env *env)
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
		//expand_var(env, &tok->content);
	}
}


void	handler_expand(t_token **token, t_env *env, t_token *tok)
{
	t_token	*tmp;

	(void)env;
	(void)token;
	tmp = NULL;
	trim_quotes(*token);
	while (tok)
	{
		check_exp(tok, env);
		check_tokens(tok);
	}
}