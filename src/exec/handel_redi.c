#include "../../includes/parse.h"

void	handel_heredoc(int *fd_in, char *file)
{
	if (file)
		*fd_in = open(file, O_RDONLY, 0777);
}
void	handel_red(t_cmd *cmd, int *fd_in, int *fd_out,char **files)
{
	t_redi		*red;
	static int	heredoc_file;

	red = cmd->in;
	while (red)
	{
		if (red->type == heredoc && files)
			handel_heredoc(fd_in, files[heredoc_file++]);
		else if (red->type == in)
			*fd_in = open(red->file, O_RDONLY, 0777);
		if (*fd_in == -1)
			return (ft_putstr_fd("minishell: ", 2), perror(red->file), exit(1));
		red = red->next;
		if (red)
			close(*fd_in);
	}
	red = cmd->out;
	while (red)
	{
		if (red->type == out)
			*fd_out = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (red->type == append)
			*fd_out = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*fd_out == -1)
			return (ft_putstr_fd("minishell: ", 2), perror(red->file), exit(1));
		red = red->next;
		if (red)
			close(*fd_out);
	}
}
