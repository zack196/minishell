#include "../../minishell.h"
#include "../../parse/parser.h"

void    error(char *msg_err)
{
    perror(msg_err);
	my_malloc(2, 1);
    exit(1);
}

char	*random_f(void)
{
	char	*file_name;
	int		file_len;
	int		fd_rd;
	int		fd_tmp;

	fd_rd = open("/dev/urandom", O_RDONLY, 0777);
	if (fd_rd < 0)
		return (perror("cannot open /dev/urandom"), NULL);
	file_len = 21;
	file_name = my_malloc((file_len + 1) * sizeof (char), 0);
	if (!file_name)
		return (perror("error malloc faild!"), NULL);
	file_name[0] = '/';
	file_name[1] = 't';
	file_name[2] = 'm';
	file_name[3] = 'p';
	file_name[4] = '/';
	if (read(fd_rd, file_name + 5, 16) == -1)
        error("error reading from urandom");
	close(fd_rd);
	file_name[file_len] = 0;
	fd_tmp = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_tmp < 0)
		return (random_f());
	return (close(fd_tmp), unlink(file_name), file_name);
}

void	handel_heredoc(int *fd_in, t_redi *red)
{
	char	*file;
	char	*line;
	char	*red_line;

	file = random_f();
	*fd_in = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (*fd_in == -1)
		error("error opening heredoc!\n");
	while (1)
	{
		red_line = readline(">");
		if (!ft_strcmp(red_line, red->file) || !red_line)
		{
			free(red_line);
			break ; 
		}
		line = ft_strjoin(red_line, "\n");
		write(*fd_in, line, ft_strlen(line));
		free(red_line);
	}
	close(*fd_in);
	*fd_in = open(file, O_RDONLY, 0777);
	unlink(file);
}

void	handel_red(t_cmd *cmd, int *fd_in, int *fd_out)
{
	t_redi	*red;

	red = cmd->in;
	while (red)
	{
		if (red->type == in)
			*fd_in = open(red->file, O_RDONLY , 0777);
		else if (red->type == heredoc)
			handel_heredoc(fd_in, red);
		if (*fd_in == -1)
			error(red->file);
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
			error(red->file);
		red = red->next;
		if (red)
			close(*fd_out);
	}
}
