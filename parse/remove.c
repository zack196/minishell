#include"parser.h"
void	ft_remove(t_token *tmp, t_token **curr, t_token **token)
{
	t_token	*exp;

	if (!tmp)
	{
		*token = (*curr)->next;
		ft_lstdelone_t(*curr);
		(*curr) = NULL;
	}
	else
	{
		exp = (*curr)->next;
		ft_lstdelone_t(*curr);
		tmp->next = exp;
		*curr = exp;
	}
}


void	remove_spaces(t_token **token, t_token *tok)
{
	t_token	*tmp;

	tmp = NULL;
	while (tok)
	{
		if (tok->type == SPACEE)
		{
			ft_remove(tmp, &tok, token);
		}
		else
		{
			tmp = tok;
			tok = tok->next;
		}
	}
}

int	ft_putendl_fd_2(char *s, char *str, int fd)
{
	if (!s)
	{
		write (fd, "\n", 1);
		return (0);
	}
	if (str && *str == '/')
		str++;
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
	if (str)
	{
		write(fd, "`", 1);
		while (*str)
		{
			write (fd, str, 1);
			str++;
		}
		write(fd, "\'", 1);
	}
	write (fd, "\n", 1);
	return (0);
}