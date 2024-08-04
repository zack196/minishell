#include "parser.h"
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

void	ft_lstclear_2(t_redi **lst)
{
	t_redi	*ptr;
	t_redi	*tmp;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->file);
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}
void	ft_free_tab2(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	clear_cmds(t_cmd **cmd)
{
	t_cmd	*tmp1;
	t_cmd	*tmp2;

	if (!cmd || !*cmd)
		return ;
	tmp1 = *cmd;
	while (tmp1)
	{
		if (tmp1->in)
			ft_lstclear_2(&tmp1->in);
		if (tmp1->out)
			ft_lstclear_2(&tmp1->out);
		if (tmp1->cmd)
			ft_free_tab2(tmp1->cmd);
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
}
