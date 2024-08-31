#include "../../includes/parse.h"

// char	*generate_file_random()
// {
// 	char	*file;
// 	int		fd;
// 	int		fd_urandom;

// 	fd_urandom = open("/dev/urandom", O_RDONLY, 0777);
// 	if (fd_urandom == -1)
// 		return (perror("/dev/urandom"), NULL);
// 	file = malloc(25 * sizeof (char));
// 	if (!file)
// 		return (perror("malloc failed!\n"),close(fd_urandom), NULL);
// 	file[0] = '/';
// 	file[1] = 't';
// 	file[2] = 'm';
// 	file[3] = 'p';
// 	file[4] = '/';
// 	if (read(fd_urandom, file + 5, 19) == -1)
// 		return (perror("error reading from urandom"), free(file), NULL);
// 	file[24] = '\0';
// 	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
// 	if (fd == -1)
// 		return (free(file),close(fd_urandom), generate_file_random());
// 	return (close(fd_urandom),close(fd), unlink(file), file);
// }

// void	handel_heredoc(char *delimiter, int *fd, int must_exp, t_envi *envi)
// {
// 	char	*rd_file;
// 	char	*line;

// 	rd_file = generate_file_random();
// 	*fd = open(rd_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	if (*fd == -1)
// 		return (perror("error opening the heredoc file"), free(rd_file));
// 	while (1)
// 	{
// 		line = readline(">");
// 		if (!line || !ft_strcmp(line, delimiter))
// 			break ;
// 		line = ft_strjoin(line, "\n");
// 		if (!line)
// 			return ;//ta tchof ach gha dir
// 		if (must_exp == 1)
// 			expand_var(envi, &line);
// 		write(*fd, line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(*fd);
// 	*fd = open(rd_file, O_RDONLY, 0777);
// 	free(line);
// 	unlink(rd_file);
// 	free(rd_file);
// }
void	handel_heredoc(int *fd_in, char *file)
{
	if (file)
	{
		*fd_in = open(file, O_RDONLY, 0777);
	}
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
		else 
		if (red->type == in)
			*fd_in = open(red->file, O_RDONLY, 0777);
		if (*fd_in == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(red->file);
			exit(1); //it can be a problem
		}
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
		{
			ft_putstr_fd("minishell: ", 2);
			perror(red->file);
			exit(1); //it can be a problem
		}
		red = red->next;
		if (red)
			close(*fd_out);
	}
}
