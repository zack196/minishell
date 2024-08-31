#include "../../includes/parse.h"

void	init_args(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOUBLE
			|| token->type == SINGLE || token->type == HYPHEN)
			i++;
		token = token->next;
	}
	if (!i++)
		return ;
	cmd->cmd = malloc(i * sizeof(char *));
	if (!cmd->cmd)
		return ;
	cmd->cmd[--i] = NULL;
}

void	init_cmd(t_token **token, t_cmd **cmd, t_envi **env)
{
	ft_lstadd_back_cmd(cmd, ft_lstnew_cmd());
	set_cmd(ft_lstlast_cmd(*cmd));
	rub_operator(*cmd, *token, token,env);
	init_args(*token, ft_lstlast_cmd(*cmd));
}

void	ft_free_tab2(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		// printf("[%p]\n", arr[i]);
		// printf("[%s]\n", arr[i]);
		free(arr[i]);
		arr[i] = NULL; 
		i++;
	}
	free(arr);
	arr = NULL;
}

void	fill_cmd(t_cmd *cmd, t_token *token, int *i)
{
	if (!token || token->type == SPACEE)
		return ;
	if (token && !token->content)
		return ;
	//TODO: split token if type word and fill it /////
	if ((token->type == WORD || token->type == HYPHEN || token->type == SINGLE
			|| token->type == DOUBLE) && cmd->cmd)
	{
		cmd->cmd[(*i)++] = ft_strdup(token->content);
		cmd->type = token->type;
	}
	else if (*(token->content) == '|')
	{
		if (token->next && token->next->content)
			cmd->pipe = 1;
	}
}

void	parse_cmd(t_token **token, t_cmd **cmd,t_envi **env)
{
	t_token		*tmp;
	t_token		*tmp1;
	int			i;
	static int	p;

	init_cmd(token, cmd, env);
	if (p && !ft_lstlast_cmd(*cmd)->in)
		ft_lstlast_cmd(*cmd)->pipe = p--;
	i = 0;
	tmp = *token;
	while (tmp && tmp->type != PIPE)
	{
		tmp1 = tmp;
		fill_cmd(ft_lstlast_cmd(*cmd), tmp, &i);
		tmp = tmp->next;
		ft_lstdelone_t(tmp1);
	}
	if (!tmp)
		return ;
	*token = tmp->next;
	fill_cmd(ft_lstlast_cmd(*cmd), tmp, &i);
	ft_lstdelone_t(tmp);
	if (ft_lstlast_cmd(*cmd)->pipe)
		p++;
	return (parse_cmd(token, cmd,env));
}

int	token_line(char *line, t_token **token)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (line[i])
	{
		i += take_separator(line + i, token);
		i += take_word(line + i, token, &flag);
		if (!flag)
		{
			ft_lstclear_t(token);
			ft_putstr_fd("token line \n", 2);
			return (0);
		}
	}
	return (1);
}
